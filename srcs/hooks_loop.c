/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:24 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:24 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static long	current_time_us(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000L + tv.tv_usec);
}

int	loop_hook(t_game *game)
{
	long	now;

	if (shutdown_requested())
		cleanup_exit(game);
	now = current_time_us();
	if (!game->paused && now - game->last_step_us >= game->speed_ms * 1000L)
	{
		step_grid(game);
		game->last_step_us = now;
	}
	render_grid(game);
	usleep(1000);
	return (0);
}

int	close_hook(t_game *game)
{
	cleanup_exit(game);
	return (0);
}
