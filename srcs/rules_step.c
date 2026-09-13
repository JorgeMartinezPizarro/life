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

void	step_grid(t_game *game)
{
	t_grid	*grid;
	char	*tmp;
	int		x;
	int		y;

	grid = &game->grid;
	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			grid->next[y * grid->width + x] = next_state(&game->rule,
					grid_get(grid, x, y), count_neighbors(grid, x, y));
			x++;
		}
		y++;
	}
	tmp = grid->cells;
	grid->cells = grid->next;
	grid->next = tmp;
}
