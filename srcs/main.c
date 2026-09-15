/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:27 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:27 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	init_defaults(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
	game->title = ft_strdup(DEFAULT_TITLE);
	game->cell_size = DEFAULT_CELL_SIZE;
	game->speed_ms = DEFAULT_SPEED_MS;
	game->grid.edge = DEFAULT_EDGE;
	parse_rule(&game->rule, "B3/S23");
}

static void	setup_hooks(t_game *game)
{
	mlx_hook(game->mlx.win, MLX_EVT_DESTROY, MLX_MASK_STRUCT,
		close_hook, game);
	mlx_key_hook(game->mlx.win, key_hook, game);
	mlx_loop_hook(game->mlx.mlx, loop_hook, game);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc < 2)
		usage_exit();
	init_defaults(&game);
	setup_signal_handlers();
	parse_args(&game, argc, argv);
	if (!game.grid.cells)
		error_exit("no initial grid: provide a config file or --random");
	grid_save_initial(&game.grid);
	game.pop_total = grid_count_alive(&game.grid);
	thread_pool_init(&game);
	init_mlx(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx.mlx);
	return (0);
}
