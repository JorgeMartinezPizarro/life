/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.h                                             :+:      :+:    :+:   */
/*                                                      +:+ +:+         +:+   */
/*   By: jomarti3 <jomarti3@student.42madrid.com>        +#+  +:+       +#+   */
/*                                                        +#+#+#+#+#+   +#+   */
/*   Created: 2026/09/13 16:11:53 by jomarti3                    #+#    #+#   */
/*   Updated: 2026/09/13 16:11:53 by jomarti3             ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFE_H
# define LIFE_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define WIN_TITLE			"life"
# define DEFAULT_CELL_SIZE	12
# define DEFAULT_SPEED_MS	150
# define DEFAULT_EDGE		EDGE_TORUS

# define COLOR_ALIVE		0x00FF7F
# define COLOR_DEAD			0x101018
# define COLOR_STATUS		0xFFFFFF

# define STATUS_HEIGHT		20

# define KEY_ESC			65307
# define KEY_SPACE			32
# define KEY_N				110
# define KEY_R				114

# define MLX_EVT_DESTROY	17
# define MLX_MASK_STRUCT	131072

typedef enum e_edge
{
	EDGE_FINITE,
	EDGE_TORUS,
	EDGE_MOBIUS,
	EDGE_KLEIN,
	EDGE_PROJECTIVE
}	t_edge;

typedef struct s_rule
{
	int		born[9];
	int		survive[9];
}	t_rule;

typedef struct s_grid
{
	int		width;
	int		height;
	t_edge	edge;
	char	*cells;
	char	*next;
	char	*initial;
}	t_grid;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx;

typedef struct s_game
{
	t_grid	grid;
	t_rule	rule;
	t_mlx	mlx;
	int		cell_size;
	int		speed_ms;
	int		paused;
	long	last_step_us;
	int		pop_total;
	int		pop_births;
	int		pop_deaths;
	int		generation;
}	t_game;

/* main.c */
int		main(int argc, char **argv);

/* error.c */
void	error_exit(char *msg);
void	usage_exit(void);

/* parse_args.c */
void	parse_args(t_game *game, int argc, char **argv);

/* parse_config.c */
void	parse_config(t_game *game, char *path);

/* parse_config_keys.c */
void	apply_config_key(t_game *game, char *line);
void	apply_edge(t_game *game, char *value);

/* parse_pattern.c */
void	parse_pattern(t_game *game, char **lines, int start);

/* parse_rule.c */
void	parse_rule(t_rule *rule, char *str);

/* parse_random.c */
void	parse_random(t_game *game, char *value);

/* grid_alloc.c */
void	grid_alloc(t_grid *grid, int width, int height);
void	grid_free(t_grid *grid);

/* grid_utils.c */
int		grid_get(t_grid *grid, int x, int y);
void	grid_set(t_grid *grid, int x, int y, int state);
void	grid_save_initial(t_grid *grid);
void	grid_reset(t_grid *grid);
int		grid_count_alive(t_grid *grid);

/* grid_edge.c */
int		edge_wrap_get(t_grid *grid, int x, int y);
char	*edge_label(t_edge edge);

/* rules_step.c */
int		count_neighbors(t_grid *grid, int x, int y);
void	step_grid(t_game *game);

/* mlx_init.c */
void	init_mlx(t_game *game);

/* render.c */
void	put_pixel_img(t_mlx *mlx, int x, int y, int color);
void	render_grid(t_game *game);

/* render_status.c */
void	render_status(t_game *game);

/* hooks_key.c */
int		key_hook(int keycode, t_game *game);

/* hooks_loop.c */
int		loop_hook(t_game *game);
int		close_hook(t_game *game);

/* cleanup.c */
void	cleanup_exit(t_game *game);

#endif
