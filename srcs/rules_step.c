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

int	next_state(t_rule *rule, int alive, int neighbors)
{
	if (alive)
		return (rule->survive[neighbors]);
	return (rule->born[neighbors]);
}

static void	compute_row(t_game *game, int y, int *births, int *deaths)
{
	t_grid	*grid;
	int		x;
	int		alive;
	int		next;

	grid = &game->grid;
	x = 0;
	while (x < grid->width)
	{
		alive = grid_get(grid, x, y);
		next = next_state(&game->rule, alive, count_neighbors(grid, x, y));
		if (next && !alive)
			(*births)++;
		else if (!next && alive)
			(*deaths)++;
		grid->next[y * grid->width + x] = next;
		x++;
	}
}

void	compute_rows(t_worker *w)
{
	int	y;

	w->births = 0;
	w->deaths = 0;
	y = w->y_start;
	while (y < w->y_end)
	{
		compute_row(w->game, y, &w->births, &w->deaths);
		y++;
	}
}
