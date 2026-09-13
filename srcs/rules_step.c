/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:35:02 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:35:02 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	count_neighbors(t_grid *grid, int x, int y)
{
	int	count;
	int	dx;
	int	dy;

	count = 0;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if ((dx != 0 || dy != 0) && grid_get(grid, x + dx, y + dy))
				count++;
			dx++;
		}
		dy++;
	}
	return (count);
}

static int	next_state(t_rule *rule, int alive, int neighbors)
{
	if (alive)
		return (rule->survive[neighbors]);
	return (rule->born[neighbors]);
}

static void	track_transition(t_game *game, int alive, int next)
{
	if (next && !alive)
		game->pop_births++;
	else if (!next && alive)
		game->pop_deaths++;
}

void	step_grid(t_game *game)
{
	t_grid	*grid;
	char	*tmp;
	int		x;
	int		y;
	int		alive;
	int		next;

	grid = &game->grid;
	game->pop_births = 0;
	game->pop_deaths = 0;
	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			alive = grid_get(grid, x, y);
			next = next_state(&game->rule, alive, count_neighbors(grid, x, y));
			track_transition(game, alive, next);
			grid->next[y * grid->width + x] = next;
			x++;
		}
		y++;
	}
	tmp = grid->cells;
	grid->cells = grid->next;
	grid->next = tmp;
	game->pop_total += game->pop_births - game->pop_deaths;
	game->generation++;
}
