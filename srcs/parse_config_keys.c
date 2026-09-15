/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:39 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:39 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static char	*value_after_eq(char *line, char **value)
{
	char	*eq;

	eq = ft_strchr(line, '=');
	if (!eq)
		return ("invalid config line, expected key=value");
	*value = eq + 1;
	return (NULL);
}

char	*apply_edge(t_game *game, char *value)
{
	if (!ft_strcmp(value, "finite"))
		game->grid.edge = EDGE_FINITE;
	else if (!ft_strcmp(value, "cylinder"))
		game->grid.edge = EDGE_CYLINDER;
	else if (!ft_strcmp(value, "torus") || !ft_strcmp(value, "wrap"))
		game->grid.edge = EDGE_TORUS;
	else if (!ft_strcmp(value, "mobius"))
		game->grid.edge = EDGE_MOBIUS;
	else if (!ft_strcmp(value, "klein"))
		game->grid.edge = EDGE_KLEIN;
	else if (!ft_strcmp(value, "projective"))
		game->grid.edge = EDGE_PROJECTIVE;
	else
		return ("invalid edge value: finite|cylinder|torus|mobius|klein"
			"|projective");
	return (NULL);
}

char	*apply_config_key(t_game *game, char *line)
{
	char	*value;
	char	*msg;

	msg = value_after_eq(line, &value);
	if (msg)
		return (msg);
	if (!ft_strncmp(line, "rule=", 5))
		return (parse_rule(&game->rule, value));
	else if (!ft_strncmp(line, "cell_size=", 10))
		game->cell_size = ft_atoi(value);
	else if (!ft_strncmp(line, "speed_ms=", 9))
		game->speed_ms = ft_atoi(value);
	else if (!ft_strncmp(line, "edge=", 5))
		return (apply_edge(game, value));
	else if (!ft_strncmp(line, "random=", 7) && !game->grid.cells)
		return (parse_random(game, value));
	else if (!ft_strncmp(line, "random=", 7))
		return ("config file: random= given after grid already set");
	else
		return ("unknown config key");
	return (NULL);
}
