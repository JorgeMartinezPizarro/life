/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 16:20:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 16:20:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static int	wrap_coord(int v, int max)
{
	return (((v % max) + max) % max);
}

static void	apply_flip(t_grid *grid, int *cx, int *cy, int out_flags)
{
	if (grid->edge != EDGE_TORUS && grid->edge != EDGE_CYLINDER
		&& (out_flags & 1))
		*cy = grid->height - 1 - *cy;
	if (grid->edge == EDGE_PROJECTIVE && (out_flags & 2))
		*cx = grid->width - 1 - *cx;
}

int	edge_wrap_get(t_grid *grid, int x, int y)
{
	int	cx;
	int	cy;
	int	x_out;
	int	y_out;

	x_out = (x < 0 || x >= grid->width);
	y_out = (y < 0 || y >= grid->height);
	if ((grid->edge == EDGE_MOBIUS || grid->edge == EDGE_CYLINDER) && y_out)
		return (0);
	cx = wrap_coord(x, grid->width);
	cy = wrap_coord(y, grid->height);
	apply_flip(grid, &cx, &cy, x_out | (y_out << 1));
	return (grid->cells[cy * grid->width + cx]);
}

char	*edge_label(t_edge edge)
{
	if (edge == EDGE_FINITE)
		return ("finite");
	if (edge == EDGE_CYLINDER)
		return ("cylinder");
	if (edge == EDGE_TORUS)
		return ("torus");
	if (edge == EDGE_MOBIUS)
		return ("mobius");
	if (edge == EDGE_KLEIN)
		return ("klein");
	return ("projective");
}
