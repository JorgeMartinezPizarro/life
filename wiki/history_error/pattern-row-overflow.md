# bug heap buffer overflow in pattern read [**Sep 14 2026**]

|  |  |
| --- | --- |
| **Badness** | Critical - reading memory out of bounds |
| **Where** | `srcs/parse_pattern.c:48` in `fill_row` |
| **Type** | CWE-125 |
| **Checked with** | AddressSanitizer and valgrind |
| **Git branch** | `fix/pattern-overflow` |

---

## 1. what is the bug

```c
static void fill_row(t_grid *grid, int row, char *line)
{
  int x;

  x = 0;
  while (x < grid->width)        /* <-- line 48 */
  {
    if (line[x] == 'o')        /* <-- line 50, reading too far! */
      grid_set(grid, x, row, 1);
    x++;
  }
}

```

the `grid->width` is made in `pattern_width()` and it is the size of the **longest** line in the file.
but `ft_split` does `malloc(len + 1)` for each line, so exactly the string lenght + 1 bytes.
If we have a row that is shorter then the longest one, it gets passed to the function anyway.

We have a off-by-one thing. `line[len]` is okay because its the `\0`, but then the loop keeps going to `line[len + 1]` if the row is 2 or more chars shorter than the maximum width.

## 2. why it is so bad

> this is the worst kind of bug because **it doesnt crash normally.**

```bash
./life /tmp/break1.cfg     # works fine no errors...

```

reading out of bounds just gives back whatever garbage byte is next in memory.
this makes 3 problems:

* **Silent wrong outputs.** If the garbage byte is a 'o', it makes a live cell that was not in the file. everything after is wrong.
* **Randomness.** The garbage byte is different on different laptops or libc. "Works on my machine" but fails for the evaluator, or maybe segfaults there.
* **its real memory corruption.** valgrind or ASAN shows it red.

we never saw it before because the configs in the folder are padded with `.` so they are all same length. if someone types a pattern manualy and leaves a line short, it breaks.

## 3. how to test it

compile with debug:

```bash
make
cc -g3 -fsanitize=address,undefined -Iincludes -Ilibft/includes -Iminilibx srcs/*.c libft/libft.a -Lminilibx -lmlx -lXext -lX11 -lbsd -lm -o life_debug

```

make a break file (only 3 lines):

```bash
printf 'PATTERN\n.o\nooooooooooooooooooooooooooooo\n' > /tmp/break1.cfg

```

row 1 is short (3 bytes), row 2 is long (29 bytes). `fill_row` will read 29 times on a 3 byte alloc.

run it:

```bash
( unset DISPLAY; ASAN_OPTIONS=detect_leaks=0 ./life_debug /tmp/break1.cfg )

```

## 4. what it prints BEFORE fixing

AddressSanitizer says:

```
==3399369==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6020000000b3
READ of size 1 at 0x6020000000b3 thread T0
    #0 0x4cf5ab in fill_row /goinfre/dlesieur/life/srcs/parse_pattern.c:50:7
...
0x6020000000b3 is located 0 bytes to the right of 3-byte region...
allocated by thread T0 here:
    ... in ft_split

```

how to read this:

* `heap-buffer-overflow` = we walked out of the malloc
* `#0 fill_row ...:50` = the exact line of the bug
* `allocated by ... ft_split` = whose memory we step on. here it is a string from ft_split.

normal build:

```bash
$ ./life /tmp/break1.cfg
$ echo $?
0

```

it says nothing! very dangerous.

## 5. how to fix

the rule is: `fill_row` should only read inside the `line` it got.
we are using a limit (`grid->width`) that belongs to a different thing (the grid).

missing chars is fine, a short row just means "the rest is empty cells". the grid is already `ft_calloc` so its full of 0s already. we dont have to write them manually.

just stop if we hit the end of the line:

```c
  while (x < grid->width && line[x])

```

this is the only change! just add `&& line[x]` on line 48.
it stops at the `\0` before we read bad memory.

## 6. what it prints AFTER fix

compile and run same thing again.

```
life: error: mlx_init failed

```

this is **good**! it parsed the whole file with no ASAN errors, and then stopped only cause we unset DISPLAY so no window can open.
valgrind is now silent too.

## 7. regression check

```bash
for c in glider pulsar fortress quadcannons; do
  printf '%-14s' "$c"
  ( unset DISPLAY; ASAN_OPTIONS=detect_leaks=0 ./life_debug configs/$c.cfg ) 2>&1 | head -1
done

```

they should all just say mlx_init failed and no memory errors.
also run with display to make sure glider still moves right so we know the fix didnt break the game.
of course we need to test further to be sure that everything is totally OK. Taht's why we would need a CI there.

## 9. Moral

**your loop max must belong to the array u are reading.** `grid->width` is for grid, `line` has its own length. this is super common bug in C.
also **bugs that dont crash are worse.** always compile with `-fsanitize=address` while coding so it screams at you when it happens.