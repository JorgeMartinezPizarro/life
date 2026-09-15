#!/usr/bin/env bash
#
# Exercises ./life under three tools, always one at a time on its own
# process -- ASan and TSan can't even be linked into the same binary,
# and valgrind must never wrap a sanitized binary either way:
#   - ASan/UBSan  (make debug,      ./life_debug) -- memory safety/UB
#   - TSan/UBSan  (make debug-tsan, ./life_tsan)  -- data races
#   - valgrind    (make/make re,    ./life)       -- memcheck + helgrind
#
# ASan/TSan overhead is low (~2-5x), so those passes also cover the
# big, performance-relevant grids. Valgrind's overhead (20-50x, more
# under helgrind) makes those grids impractical to fully exercise, so
# its pass sticks to small/moderate grids by default.
#
# Usage: scripts/stress_test.sh [--all-configs]
#   ASAN_SECS=5 TSAN_SECS=8 VALGRIND_SECS=30 scripts/stress_test.sh
#
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

ASAN_SECS="${ASAN_SECS:-5}"
TSAN_SECS="${TSAN_SECS:-8}"
VALGRIND_SECS="${VALGRIND_SECS:-30}"
TS="$(date +%Y%m%d_%H%M%S)"
OUT="$ROOT/test_logs/$TS"
mkdir -p "$OUT"

# ASan pass: cheap enough to include the large, perf-relevant grids.
ASAN_CASES=(
	"configs/glider.cfg"
	"configs/fullscreen_conway.cfg"
	"--random=1900x1000:30"
)
if [ "${1:-}" = "--all-configs" ]; then
	ASAN_CASES=()
	while IFS= read -r f; do
		ASAN_CASES+=("$f")
	done < <(find configs -name '*.cfg' | sort)
	ASAN_CASES+=("--random=1900x1000:30")
fi

# Valgrind pass: small/moderate grids only -- see the overhead note above.
VALGRIND_CASES=(
	"configs/glider.cfg"
	"--random=300x200:30"
)

INVALID_CASES=(
	"scripts/bad_configs/bad_rule.cfg"
	"scripts/bad_configs/bad_both.cfg"
	"scripts/bad_configs/bad_pattern_ragged.cfg"
	"scripts/bad_configs/bad_pattern_empty.cfg"
	"scripts/bad_configs/bad_pattern_invalid.cfg"
)

FAILURES=0
INCONCLUSIVE=0

echo "== building release (make re) =="
make re >"$OUT/build_release.log" 2>&1 \
	|| { echo "release build failed, see $OUT/build_release.log"; exit 1; }

echo "== building sanitizer debug (make debug) =="
make debug >"$OUT/build_debug.log" 2>&1 \
	|| { echo "debug build failed, see $OUT/build_debug.log"; exit 1; }

echo "== building ThreadSanitizer debug (make debug-tsan) =="
make debug-tsan >"$OUT/build_tsan.log" 2>&1 \
	|| { echo "tsan build failed, see $OUT/build_tsan.log"; exit 1; }

slug() { printf '%s' "$1" | tr -c 'A-Za-z0-9._-' '_'; }

# ASan/UBSan pass: runs ./life_debug alone, never under valgrind.
run_asan() {
	local args="$1" secs="$2" log="$3"
	ASAN_OPTIONS="detect_leaks=1:halt_on_error=1:abort_on_error=1" \
	UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1" \
	timeout -k 2 "$secs" ./life_debug $args >"$log" 2>&1
	echo $?
}

# TSan/UBSan pass: runs ./life_tsan alone -- never together with the
# ASan binary (mutually exclusive by design) or under valgrind.
# `setarch -R` disables ASLR: TSan's fixed shadow-memory layout can
# otherwise fail at startup with "unexpected memory mapping" under
# WSL2/some kernels -- not a bug in this program, just how TSan copes
# (or doesn't) with the address space it's handed.
run_tsan() {
	local args="$1" secs="$2" log="$3"
	TSAN_OPTIONS="halt_on_error=1" \
	UBSAN_OPTIONS="print_stacktrace=1:halt_on_error=1" \
	timeout -k 2 "$secs" setarch "$(uname -m)" -R ./life_tsan $args >"$log" 2>&1
	echo $?
}

# Valgrind pass: runs the plain ./life build, never the sanitized one.
run_valgrind() {
	local tool="$1" args="$2" secs="$3" log="$4"
	local extra=()
	if [ "$tool" = "memcheck" ]; then
		extra=(--tool=memcheck --leak-check=full \
			--show-leak-kinds=definite,indirect --track-origins=yes)
	else
		extra=(--tool=helgrind)
	fi
	timeout -k 5 "$secs" valgrind "${extra[@]}" --error-exitcode=97 \
		--suppressions="$ROOT/scripts/valgrind.supp" \
		-- ./life $args >"$log" 2>&1
	echo $?
}

check_asan_log() {
	grep -Eq 'ERROR: (Address|LeakSanitizer)|runtime error:|FATAL: (Address|LeakSanitizer)' "$1"
}

check_tsan_log() {
	grep -Eq 'WARNING: ThreadSanitizer|SUMMARY: ThreadSanitizer|FATAL: ThreadSanitizer' "$1"
}

# Valgrind prints "ERROR SUMMARY" whenever it gets to finish reporting,
# whether the run ended normally or was stopped by a signal it could
# still handle (e.g. SIGTERM from `timeout`). No such line at all means
# it got SIGKILLed mid-run (too slow for the given VALGRIND_SECS) and
# the log proves nothing either way.
#
# NB: valgrind counts its own "Process terminating with default action
# of signal 15 (SIGTERM)" note (printed on every run this script kills
# on purpose) towards ERROR SUMMARY, so that count alone is not a
# reliable signal -- key off the actual error headers instead.
check_valgrind_status() {
	local log="$1"
	if grep -Eq 'Invalid (read|write|free)|Use of uninitialised value|Conditional jump or move depends on uninitialised|Syscall param .* points to uninitialised|Mismatched free|Source and destination overlap|[Pp]ossible data race|lock order|definitely lost: [1-9]' "$log"; then
		echo fail
	elif ! grep -q 'ERROR SUMMARY' "$log"; then
		echo inconclusive
	else
		echo ok
	fi
}

report() {
	local label="$1" status="$2" detail="${3:-}"
	if [ "$status" = ok ]; then
		echo "  [OK]   $label"
	else
		echo "  [FAIL] $label -> $detail"
		FAILURES=$((FAILURES + 1))
	fi
}

echo
echo "== valid configs: ASan/UBSan via ./life_debug (make debug) =="
for args in "${ASAN_CASES[@]}"; do
	s="$(slug "$args")"
	log="$OUT/asan_${s}.log"
	code="$(run_asan "$args" "$ASAN_SECS" "$log")"
	if check_asan_log "$log"; then
		report "$args (asan, exit=$code)" fail "sanitizer flagged an issue, see $log"
	else
		note="ran $ASAN_SECS s"
		[ "$code" = 124 ] && note="killed by timeout after ${ASAN_SECS}s, expected"
		report "$args (asan, exit=$code, $note)" ok
	fi
done

echo
echo "== valid configs: ThreadSanitizer via ./life_tsan (make debug-tsan) =="
for args in "${ASAN_CASES[@]}"; do
	s="$(slug "$args")"
	log="$OUT/tsan_${s}.log"
	code="$(run_tsan "$args" "$TSAN_SECS" "$log")"
	if check_tsan_log "$log"; then
		report "$args (tsan, exit=$code)" fail "data race flagged, see $log"
	else
		note="ran $TSAN_SECS s"
		[ "$code" = 124 ] && note="killed by timeout after ${TSAN_SECS}s, expected"
		report "$args (tsan, exit=$code, $note)" ok
	fi
done

echo
echo "== valid configs: valgrind memcheck + helgrind via plain ./life (small grids only) =="
for args in "${VALGRIND_CASES[@]}"; do
	s="$(slug "$args")"
	for tool in memcheck helgrind; do
		log="$OUT/valgrind_${tool}_${s}.log"
		code="$(run_valgrind "$tool" "$args" "$VALGRIND_SECS" "$log")"
		status="$(check_valgrind_status "$log")"
		if [ "$status" = inconclusive ]; then
			echo "  [??]   $args ($tool, exit=$code) -> killed before it could report, raise VALGRIND_SECS; see $log"
			INCONCLUSIVE=$((INCONCLUSIVE + 1))
		else
			report "$args ($tool, exit=$code)" "$status" "see $log"
		fi
	done
done

echo
echo "== invalid configs: ASan/UBSan, expect exit(1) -- leaks in the error path ARE real bugs =="
for args in "${INVALID_CASES[@]}"; do
	s="$(slug "$args")"
	log="$OUT/asan_invalid_${s}.log"
	code="$(run_asan "$args" "$ASAN_SECS" "$log")"
	if check_asan_log "$log"; then
		report "$args (asan, exit=$code)" fail "see $log"
	else
		report "$args (asan, exit=$code)" ok
	fi
done

echo
echo "== invalid configs: valgrind memcheck, expect exit(1) -- leaks in the error path ARE real bugs =="
for args in "${INVALID_CASES[@]}"; do
	s="$(slug "$args")"
	log="$OUT/valgrind_memcheck_invalid_${s}.log"
	code="$(run_valgrind "memcheck" "$args" "$VALGRIND_SECS" "$log")"
	status="$(check_valgrind_status "$log")"
	if [ "$status" = inconclusive ]; then
		echo "  [??]   $args (memcheck, exit=$code) -> killed before it could report, raise VALGRIND_SECS; see $log"
		INCONCLUSIVE=$((INCONCLUSIVE + 1))
	else
		report "$args (memcheck, exit=$code)" "$status" "see $log"
	fi
done

echo
echo "logs in $OUT"
if [ "$INCONCLUSIVE" -gt 0 ]; then
	echo "$INCONCLUSIVE run(s) inconclusive (killed before valgrind finished reporting)."
fi
if [ "$FAILURES" -gt 0 ]; then
	echo "$FAILURES check(s) flagged: crash, invalid access, data race, or a leak on an error path."
	exit 1
fi
echo "no confirmed failures."
