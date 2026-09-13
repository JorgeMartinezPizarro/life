/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 16:30:00 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 16:30:00 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static char	*num_field(char *label, int value)
{
	char	*num;
	char	*labeled;
	char	*out;

	num = ft_itoa(value);
	labeled = ft_strjoin(label, num);
	free(num);
	out = ft_strjoin(labeled, "  ");
	free(labeled);
	return (out);
}

static char	*build_status(t_game *game)
{
	char	*total;
	char	*births;
	char	*deaths;
	char	*line;

	total = num_field("total: ", game->pop_total);
	births = num_field("births: ", game->pop_births);
	deaths = num_field("deaths: ", game->pop_deaths);
	line = ft_strjoin(total, births);
	free(total);
	free(births);
	total = line;
	line = ft_strjoin(total, deaths);
	free(total);
	free(deaths);
	return (line);
}

void	render_status(t_game *game)
{
	char	*line;
	int		y;

	line = build_status(game);
	if (!line)
		return ;
	y = game->grid.height * game->cell_size + STATUS_HEIGHT / 2 + 4;
	mlx_string_put(game->mlx.mlx, game->mlx.win, 5, y, COLOR_STATUS, line);
	free(line);
}
