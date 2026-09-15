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

static char	*build_status(t_game *game)
{
	char	*line;
	char	*rule;

	line = ft_strdup("");
	line = append(line, str_field("geometry: ", edge_label(game->grid.edge)));
	rule = rule_label(&game->rule);
	line = append(line, str_field("rule: ", rule));
	free(rule);
	line = append(line, num_field("gen: ", game->generation));
	line = append(line, num_field("total: ", game->pop_total));
	line = append(line, num_field("births: ", game->pop_births));
	line = append(line, num_field("deaths: ", game->pop_deaths));
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
