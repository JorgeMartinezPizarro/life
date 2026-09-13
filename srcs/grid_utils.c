/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:16 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:16 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

int	grid_get(t_grid *grid, int x, int y)
{
	if (grid->edge == EDGE_FINITE)
	{
		if (x < 0 || x >= grid->width || y < 0 || y >= grid->height)
			return (0);
		return (grid->cells[y * grid->width + x]);
	}
	return (edge_wrap_get(grid, x, y));
}

void	grid_set(t_grid *grid, int x, int y, int state)
{
	if (x < 0 || x >= grid->width || y < 0 || y >= grid->height)
		return ;
	grid->cells[y * grid->width + x] = (char)state;
}

void	grid_save_initial(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->width * grid->height)
	{
		grid->initial[i] = grid->cells[i];
		i++;
	}
}

void	grid_reset(t_grid *grid)
{
	int	i;

	i = 0;
	while (i < grid->width * grid->height)
	{
		grid->cells[i] = grid->initial[i];
		i++;
	}
}
