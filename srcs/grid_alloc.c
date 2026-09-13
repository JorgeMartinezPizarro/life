/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:13 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	grid_alloc(t_grid *grid, int width, int height)
{
	grid->width = width;
	grid->height = height;
	grid->cells = ft_calloc((size_t)(width * height), sizeof(char));
	grid->next = ft_calloc((size_t)(width * height), sizeof(char));
	grid->initial = ft_calloc((size_t)(width * height), sizeof(char));
	if (!grid->cells || !grid->next || !grid->initial)
		error_exit("malloc failed while allocating grid");
}

void	grid_free(t_grid *grid)
{
	free(grid->cells);
	free(grid->next);
	free(grid->initial);
	grid->cells = NULL;
	grid->next = NULL;
	grid->initial = NULL;
}
