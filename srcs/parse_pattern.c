/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:47 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:47 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static int	pattern_height(char **lines, int start)
{
	size_t	h;

	h = 0;
	while (lines[start + h] && lines[start + h][0] != '\0')
		h++;
	return (safe_len(h));
}

static int	pattern_width(char **lines, int start, int height)
{
	size_t	w;
	size_t	len;
	int		i;

	w = 0;
	i = 0;
	while (i < height)
	{
		len = ft_strlen(lines[start + i]);
		if (len > w)
			w = len;
		i++;
	}
	return (safe_len(w));
}

static void	fill_row(t_grid *grid, int row, char *line)
{
	int	x;

	x = 0;
	while (x < grid->width)
	{
		if (line[x] == 'o')
			grid_set(grid, x, row, 1);
		x++;
	}
}

void	parse_pattern(t_game *game, char **lines, int start)
{
	int	height;
	int	width;
	int	y;

	height = pattern_height(lines, start);
	width = pattern_width(lines, start, height);
	if (height == 0 || width == 0)
		error_exit("empty pattern in config file");
	grid_alloc(&game->grid, width, height);
	y = 0;
	while (y < height)
	{
		fill_row(&game->grid, y, lines[start + y]);
		y++;
	}
}
