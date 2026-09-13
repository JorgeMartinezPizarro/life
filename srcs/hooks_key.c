/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:20 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:20 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	key_hook(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		cleanup_exit(game);
	else if (keycode == KEY_SPACE)
		game->paused = !game->paused;
	else if (keycode == KEY_N && game->paused)
		step_grid(game);
	else if (keycode == KEY_R)
		grid_reset(&game->grid);
	return (0);
}
