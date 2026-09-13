# life

Conway's Game of Life, written in C following the 42 Norm, rendered with
[minilibX](minilibx/). Initial conditions and the cellular-automaton rule
are fully configurable, either through a config file or CLI flags.

![Demo de life](assets/life.gif)

## Build

This project links against X11/Xext through minilibX, so it needs a Linux
environment with an X server. On Windows, build and run it from **WSL**
(WSLg provides the display out of the box):

```
sudo apt-get install gcc make xorg libxext-dev libbsd-dev   # once, if missing
make
```

- `make` builds `minilibx/libmlx.a`, then `libft/libft.a`, then `life`.
- `make clean` removes object files (life's own, libft's, minilibx's).
- `make fclean` also removes the `life` binary and the two `.a` libraries.
- `make re` = `fclean` + `all`.

## Run

```
./life <config_file> [options]
./life --random=WxH:PERCENT [options]
```

You need either a config file (which supplies the initial grid) or
`--random=WxH:PERCENT` to build one on the fly. Try:

```
./life configs/default.cfg           # Gosper glider gun, 960x720 window
./life configs/glider.cfg
./life configs/blinker.cfg
./life configs/fullscreen.cfg        # 1900x1000 random soup, cell_size=1, Conway
./life configs/fullscreen_conway.cfg    # 1900x1000 px, cell_size=2, B3/S23     - dies down fastest
./life configs/fullscreen_highlife.cfg  # 1900x1000 px, cell_size=2, B36/S23    - freezes even faster than Conway
./life configs/fullscreen_daynight.cfg  # 1900x1000 px, cell_size=2, B3678/S34678 - stays churning the longest
./life configs/random.cfg            # random grid generated from the config file itself
./life --random=100x70:25 --rule=B36/S23 --cell=10
```

The three `fullscreen_*` configs are the same random seed and grid at three
different rules, meant to be compared side by side: no finite grid can stay
chaotic forever (see below), but some rules take far longer than others to
settle into "ash". `daynight` sustains visible activity by far the longest
of the three.

### Controls

| Key     | Action                              |
|---------|--------------------------------------|
| `ESC`   | quit                                  |
| `SPACE` | pause / resume                        |
| `N`     | advance one generation (while paused) |
| `R`     | reset to the initial pattern          |
| close (X) button | quit                         |

### CLI options

| Flag | Meaning |
|------|---------|
| `--rule=Bxxx/Sxxx` | life-like rule, e.g. `B3/S23` (Conway), `B36/S23` (HighLife) |
| `--random=WxH:PCT` | build a `W`x`H` grid, each cell alive with `PCT`% probability (0-100); needed if no config file is given |
| `--speed=ms` | milliseconds between generations |
| `--cell=px` | pixel size of one cell |
| `--edge=wrap\|finite` | `wrap`: toroidal grid (default); `finite`: cells outside the grid count as dead |

Flags override whatever the config file set. `--random` and a config file
are mutually exclusive as the grid source (the first one seen wins).

## Config file format

```
# comment lines start with #
rule=B3/S23
cell_size=12
speed_ms=80
edge=wrap
PATTERN
....................
....................
.........ooo........
....................
....................
```

- `rule=` — life-like rule string, `B<digits>/S<digits>`.
- `cell_size=` — pixel size of one cell in the window.
- `speed_ms=` — milliseconds between generations.
- `edge=` — `wrap` or `finite` (see above).
- `PATTERN` — marks the start of the grid. Everything after it, to the end
  of the file, is the initial pattern: one line per row. `o`, `O`, `*` or
  `1` mean an alive cell; anything else (typically `.`) means dead. The
  grid's width is the longest pattern line; shorter lines are padded with
  dead cells on the right, so the block doesn't need to be a perfect
  rectangle.
- `random=WxH:PCT` — build a random `W`x`H` grid instead of a `PATTERN`
  block, same format as `--random` on the CLI. A file uses **either**
  `random=` **or** `PATTERN`, never both — see `configs/random.cfg`.

All keys are optional; anything not set falls back to a sane default
(`B3/S23`, `cell_size=10`, `speed_ms=150`, `edge=wrap`) or to a
`--flag` given on the command line.

## Project layout

```
Makefile            life's own sources + link step (-lft -lmlx)
includes/life.h      shared types and prototypes
srcs/                life's own .c files (parsing, grid, rendering, hooks)
libft/               personal libft + ft_printf + get_next_line, own Makefile -> libft.a
minilibx/             vendored minilibX (own Makefile -> libmlx.a)
configs/              example config files
```

## Shortcuts

In windows, you can capture with `Win + G` and then use the `mp4` as follows to create a gif:

```powershell
ffmpeg -i './cube.mp4' -vf "fps=15,scale=800:-1:flags=lanczos,palettegen" palette.png

ffmpeg -i 'cube.mp4' -i palette.png -lavfi "fps=15,scale=800:-1:flags=lanczos[x];[x][1:v]paletteuse" Cub3D.gif
```