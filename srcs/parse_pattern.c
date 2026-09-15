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
	size_t	first_len;
	size_t	len;
	int		i;

	first_len = ft_strlen(lines[start]);
	i = 1;
	while (i < height)
	{
		len = ft_strlen(lines[start + i]);
		if (len != first_len)
			error_exit("pattern is not rectangular: all rows must have "
				"the same length");
		i++;
	}
	return (safe_len(first_len));
}

static void	fill_row(t_grid *grid, int row, char *line)
{
	int	x;

	x = 0;
	while (x < grid->width && line[x] != '\0')
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
	if (height == 0)
		error_exit("empty pattern in config file");
	width = pattern_width(lines, start, height);
	if (width == 0)
		error_exit("empty pattern in config file");
	if (width > MAX_GRID_WIDTH || height > MAX_GRID_HEIGHT)
		error_exit("pattern dimensions exceed maximum allowed size");
	grid_alloc(&game->grid, width, height);
	y = 0;
	while (y < height)
	{
		fill_row(&game->grid, y, lines[start + y]);
		y++;
	}
}
