/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:44 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:44 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	strip_cr_all(char **lines)
{
	int		i;
	size_t	len;

	i = 0;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] == '\r')
			lines[i][len - 1] = '\0';
		i++;
	}
}

/*
** Nothing here ever calls error_exit() directly except parse_config()
** itself: apply_config_key()/parse_pattern() and everything they call
** (parse_rule, parse_random, apply_edge) return an error message (or
** NULL) instead. That keeps `lines` freed exactly once, right where
** it's owned, no matter how deep the actual failure occurred.
*/
static char	*find_pattern_start(t_game *game, char **lines, int *start)
{
	int		i;
	char	*msg;

	i = 0;
	while (lines[i])
	{
		if (!ft_strncmp(lines[i], "PATTERN", 7) && lines[i][7] == '\0')
		{
			*start = i + 1;
			return (NULL);
		}
		if (lines[i][0] && lines[i][0] != '#')
		{
			msg = apply_config_key(game, lines[i]);
			if (msg)
				return (msg);
		}
		i++;
	}
	*start = -1;
	return (NULL);
}

static void	fail(char **lines, char *msg)
{
	ft_free_split(lines);
	error_exit(msg);
}

static char	*resolve_source(t_game *game, char **lines, int start)
{
	if (start < 0 && !game->grid.cells)
		return ("config file needs a PATTERN section or a random= line");
	if (start >= 0 && game->grid.cells)
	{
		grid_free(&game->grid);
		return ("config file has both random= and PATTERN, use only one");
	}
	if (start >= 0)
		return (parse_pattern(game, lines, start));
	return (NULL);
}

void	parse_config(t_game *game, char *path)
{
	char	*content;
	char	**lines;
	int		start;
	char	*msg;

	content = ft_read_file(path);
	if (!content)
		error_exit("cannot read config file");
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		error_exit("invalid config file");
	strip_cr_all(lines);
	msg = find_pattern_start(game, lines, &start);
	if (!msg)
		msg = resolve_source(game, lines, start);
	if (msg)
		fail(lines, msg);
	ft_free_split(lines);
}
