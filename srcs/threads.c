/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 19:52:14 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/15 19:52:21 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	init_workers(t_game *game)
{
	int	rows_per;
	int	extra;
	int	y;
	int	i;

	rows_per = game->grid.height / THREAD_COUNT;
	extra = game->grid.height % THREAD_COUNT;
	y = 0;
	i = 0;
	while (i < THREAD_COUNT)
	{
		game->pool.workers[i].game = game;
		game->pool.workers[i].y_start = y;
		y += rows_per + (i < extra);
		game->pool.workers[i].y_end = y;
		i++;
	}
}

static void	*worker_main(void *arg)
{
	t_worker	*w;
	t_pool		*pool;
	int			seen_gen;

	w = (t_worker *)arg;
	pool = &w->game->pool;
	seen_gen = 0;
	pthread_mutex_lock(&pool->lock);
	while (1)
	{
		while (pool->generation == seen_gen && !pool->stop)
			pthread_cond_wait(&pool->work_cond, &pool->lock);
		if (pool->stop)
			break ;
		seen_gen = pool->generation;
		pthread_mutex_unlock(&pool->lock);
		compute_rows(w->game, w->y_start, w->y_end, &w->births, &w->deaths);
		pthread_mutex_lock(&pool->lock);
		pool->done_count++;
		if (pool->done_count == THREAD_COUNT)
			pthread_cond_signal(&pool->done_cond);
	}
	pthread_mutex_unlock(&pool->lock);
	return (NULL);
}

void	thread_pool_init(t_game *game)
{
	t_pool	*pool;
	int		i;

	pool = &game->pool;
	init_workers(game);
	pthread_mutex_init(&pool->lock, NULL);
	pthread_cond_init(&pool->work_cond, NULL);
	pthread_cond_init(&pool->done_cond, NULL);
	pool->generation = 0;
	pool->done_count = 0;
	pool->stop = 0;
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_create(&pool->tids[i], NULL, worker_main, &pool->workers[i]);
		i++;
	}
}

void	thread_pool_destroy(t_game *game)
{
	t_pool	*pool;
	int		i;

	pool = &game->pool;
	pthread_mutex_lock(&pool->lock);
	pool->stop = 1;
	pthread_cond_broadcast(&pool->work_cond);
	pthread_mutex_unlock(&pool->lock);
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(pool->tids[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&pool->lock);
	pthread_cond_destroy(&pool->work_cond);
	pthread_cond_destroy(&pool->done_cond);
}

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

static void	print_step_time(t_game *game, long us)
{
	ft_putstr_fd("gen ", 1);
	ft_putnbr_fd(game->generation, 1);
	ft_putstr_fd(": step time ", 1);
	ft_putnbr_fd((int)us, 1);
	ft_putstr_fd(" us (", 1);
	ft_putnbr_fd(THREAD_COUNT, 1);
	ft_putendl_fd(" threads)", 1);
}

void	step_grid(t_game *game)
{
	t_grid			*grid;
	char			*tmp;
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	dispatch_step(&game->pool);
	reduce_counts(game);
	grid = &game->grid;
	tmp = grid->cells;
	grid->cells = grid->next;
	grid->next = tmp;
	game->pop_total += game->pop_births - game->pop_deaths;
	game->generation++;
	gettimeofday(&end, NULL);
	print_step_time(game, (end.tv_sec - start.tv_sec) * 1000000L
		+ (end.tv_usec - start.tv_usec));
}
