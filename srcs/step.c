/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 20:45:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/15 20:45:07 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	dispatch_step(t_pool *pool)
{
	pthread_mutex_lock(&pool->lock);
	pool->done_count = 0;
	pool->generation++;
	pthread_cond_broadcast(&pool->work_cond);
	while (pool->done_count != THREAD_COUNT)
		pthread_cond_wait(&pool->done_cond, &pool->lock);
	pthread_mutex_unlock(&pool->lock);
}

static void	reduce_counts(t_game *game)
{
	int	i;

	game->pop_births = 0;
	game->pop_deaths = 0;
	i = 0;
	while (i < THREAD_COUNT)
	{
		game->pop_births += game->pool.workers[i].births;
		game->pop_deaths += game->pool.workers[i].deaths;
		i++;
	}
}

void	step_grid(t_game *game)
{
	t_grid	*grid;
	char	*tmp;

	dispatch_step(&game->pool);
	reduce_counts(game);
	grid = &game->grid;
	tmp = grid->cells;
	grid->cells = grid->next;
	grid->next = tmp;
	game->pop_total += game->pop_births - game->pop_deaths;
	game->generation++;
}
