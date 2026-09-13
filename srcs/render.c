/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:58 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:58 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	put_pixel_img(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;

	pixel = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)pixel = (unsigned int)color;
}

static void	draw_cell(t_game *game, int gx, int gy, int color)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = gx * game->cell_size;
	py = gy * game->cell_size;
	y = 0;
	while (y < game->cell_size)
	{
		x = 0;
		while (x < game->cell_size)
		{
			put_pixel_img(&game->mlx, px + x, py + y, color);
			x++;
		}
		y++;
	}
}

void	render_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->grid.height)
	{
		x = 0;
		while (x < game->grid.width)
		{
			if (grid_get(&game->grid, x, y))
				draw_cell(game, x, y, COLOR_ALIVE);
			else
				draw_cell(game, x, y, COLOR_DEAD);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->mlx.img, 0, 0);
}
