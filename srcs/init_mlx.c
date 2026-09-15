/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:31 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:31 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	check_screen_fit(t_game *game)
{
	int	screen_w;
	int	screen_h;
	int	win_w;
	int	win_h;

	mlx_get_screen_size(game->mlx.mlx, &screen_w, &screen_h);
	win_w = game->grid.width * game->cell_size;
	win_h = game->grid.height * game->cell_size + STATUS_HEIGHT;
	if (win_w > screen_w || win_h > screen_h)
	{
		thread_pool_destroy(game);
		mlx_destroy_display(game->mlx.mlx);
		free(game->mlx.mlx);
		grid_free(&game->grid);
		free(game->title);
		error_exit("scenario does not fit the screen: lower --cell "
			"or shrink the grid/pattern");
	}
}

static void	create_window(t_game *game)
{
	int	win_w;
	int	win_h;

	win_w = game->grid.width * game->cell_size;
	win_h = game->grid.height * game->cell_size + STATUS_HEIGHT;
	game->mlx.win = mlx_new_window(game->mlx.mlx, win_w, win_h, game->title);
	if (!game->mlx.win)
		error_exit("mlx_new_window failed");
}

static void	create_image(t_game *game)
{
	int	win_w;
	int	win_h;

	win_w = game->grid.width * game->cell_size;
	win_h = game->grid.height * game->cell_size;
	game->mlx.img = mlx_new_image(game->mlx.mlx, win_w, win_h);
	if (!game->mlx.img)
		error_exit("mlx_new_image failed");
	game->mlx.addr = mlx_get_data_addr(game->mlx.img, &game->mlx.bpp,
			&game->mlx.line_len, &game->mlx.endian);
}

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
		error_exit("mlx_init failed");
	check_screen_fit(game);
	create_window(game);
	create_image(game);
}
