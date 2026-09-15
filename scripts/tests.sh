#!/usr/bin/env bash
#
# Exercises ./life under three tools, always one at a time on its own
# process -- ASan and TSan can't even be linked into the same binary,
# and valgrind must never wrap a sanitized binary either way:
#   - ASan/UBSan  (make debug,      ./life_debug) -- memory safety/UB
#   - TSan/UBSan  (make debug-tsan, ./life_tsan)  -- data races
#   - valgrind    (make/make re,    ./life)       -- memcheck + helgrind
#
# Default is a small curated set of configs (+ a couple of --random=
# CLI cases), tuned to land around 2-3 minutes total -- fast enough to
# run routinely. Pass --all-configs to instead sweep every
# configs/*.cfg (skipping any too big for the screen, see
# fits_test_limit below); that's thorough but can take ~40+ minutes at
# full duration, so it's opt-in, not what `make test` runs.
#
# Usage: scripts/tests.sh [--all-configs]   (or: make test)
#   ASAN_SECS=4 TSAN_SECS=5 VALGRIND_SECS=15 scripts/tests.sh
#
# The program now catches SIGINT/SIGTERM (srcs/signals.c) and runs its
# normal cleanup_exit() on the next loop tick instead of dying raw, so
# the `timeout` kill below ends every run the same way ESC would --
# leak reports for the long-running valid-config passes are therefore
# meaningful, not an artifact of being killed mid-flight.
#
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

ASAN_SECS="${ASAN_SECS:-4}"
TSAN_SECS="${TSAN_SECS:-5}"
VALGRIND_SECS="${VALGRIND_SECS:-15}"
TS="$(date +%Y%m%d_%H%M%S)"
OUT="$ROOT/test_logs/$TS"
mkdir -p "$OUT"

# The window mlx opens is grid-cells x cell_size, not grid-cells alone
# (--cell defaults to 12, includes/life.h DEFAULT_CELL_SIZE) -- an
# earlier version of this script forgot the multiplication and asked
# for a 1900x1000-cell grid with no --cell override, i.e. a
# 22800x12000px window, which froze/glitched the display. The game
# itself now also guards this (srcs/init_mlx.c check_screen_fit(),
# checked against mlx_get_screen_size()); this ceiling just keeps the
# test cases themselves small and fast, generous enough to leave
# existing configs/*.cfg (already authored to fit a real screen)
# untouched.
MAX_WIN_W=1920
MAX_WIN_H=1080

# Skips a config whose PATTERN block (or random= line, for configs
# that generate their grid instead of drawing it) at its own
# cell_size= (default 12) would open a window bigger than
# MAX_WIN_W x MAX_WIN_H, so the sweep below can't pick one up by
# accident as configs/ grows.
fits_test_limit() {
	awk -v maxw="$MAX_WIN_W" -v maxh="$MAX_WIN_H" '
		BEGIN { in_pat = 0; h = 0; w = 0; cell = 12; rw = 0; rh = 0 }
		/^cell_size=/ { cell = $0; sub(/^cell_size=/, "", cell) }
		/^random=/ {
			spec = $0
			sub(/^random=/, "", spec)
			split(spec, dims, "x")
			rw = dims[1] + 0
			split(dims[2], hp, ":")
			rh = hp[1] + 0
		}
		/^PATTERN$/ { in_pat = 1; next }
		# libft'\''s ft_split() collapses consecutive delimiters, so a
		# blank line after PATTERN never becomes an empty entry in
		# lines[] -- it'\''s silently skipped, not a stop signal, and
		# the real parser (srcs/parse_pattern.c pattern_height())
		# just keeps counting past it to end of file. Skip it here
		# too instead of stopping, to measure what the game actually
		# would.
		in_pat && $0 == "" { next }
		in_pat { h++; if (length($0) > w) w = length($0) }
		END {
			if (!in_pat) { w = rw; h = rh }
			if (w * cell > maxw || h * cell + 20 > maxh) exit 1
			exit 0
		}
	' "$1"
}

# --cell=2 on the synthetic cases keeps their window small (well under
# MAX_WIN_W x MAX_WIN_H) while still exercising real cell counts
# across the thread pool.
ASAN_CASES=(
	"configs/glider.cfg"
	"configs/fullscreen_conway.cfg"
	"--random=300x200:30 --cell=2"
)
VALGRIND_CASES=(
	"configs/glider.cfg"
	"--random=150x100:30 --cell=2"
)

if [ "${1:-}" = "--all-configs" ]; then
	CONFIG_CASES=()
	while IFS= read -r f; do
		if fits_test_limit "$f"; then
			CONFIG_CASES+=("$f")
		else
			echo "  [skip] $f exceeds ${MAX_WIN_W}x${MAX_WIN_H}px, skipping (mlx window-size freeze risk)"
		fi
	done < <(find configs -name '*.cfg' | sort)
	CONFIG_CASES+=("--random=300x200:30 --cell=2")
	ASAN_CASES=("${CONFIG_CASES[@]}")
	VALGRIND_CASES=("${CONFIG_CASES[@]}")
fi

INVALID_CASES=(
	"scripts/bad_configs/bad_rule.cfg"
	"scripts/bad_configs/bad_both.cfg"
	"scripts/bad_configs/bad_pattern_ragged.cfg"
	"scripts/bad_configs/bad_pattern_empty.cfg"
	"scripts/bad_configs/bad_pattern_invalid.cfg"
	# exercises check_screen_fit() in srcs/init_mlx.c: a 10x10 grid at
	# --cell=500 asks for a 5000x5020px window, past any real screen,
	# and unlike the fixtures above this fails after mlx_init() has
	# already opened a display connection, so it's also the only
	# invalid case that touches the mlx.mlx cleanup path.
	"--random=10x10:30 --cell=500"
)

FAILURES=0
INCONCLUSIVE=0

echo "== building release (make) =="
make >"$OUT/build_release.log" 2>&1 \
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
	timeout --preserve-status -k 2 "$secs" ./life_debug $args >"$log" 2>&1
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
	timeout --preserve-status -k 2 "$secs" setarch "$(uname -m)" -R ./life_tsan $args >"$log" 2>&1
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
	timeout --preserve-status -k 5 "$secs" valgrind "${extra[@]}" --error-exitcode=97 \
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
		[ "$code" = 0 ] && note="ran ${ASAN_SECS}s then shut down cleanly on SIGTERM, expected"
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
		[ "$code" = 0 ] && note="ran ${TSAN_SECS}s then shut down cleanly on SIGTERM, expected"
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
