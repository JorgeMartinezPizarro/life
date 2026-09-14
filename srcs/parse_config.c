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

static int	find_pattern_start(t_game *game, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (!ft_strncmp(lines[i], "PATTERN", 7) && lines[i][7] == '\0')
			return (i + 1);
		if (lines[i][0] && lines[i][0] != '#')
			apply_config_key(game, lines[i]);
		i++;
	}
	return (-1);
}

void	parse_config(t_game *game, char *path)
{
	char	*content;
	char	**lines;
	int		start;

	content = ft_read_file(path);
	if (!content)
		error_exit("cannot read config file");
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		error_exit("invalid config file");
	strip_cr_all(lines);
	start = find_pattern_start(game, lines);
	if (start < 0 && !game->grid.cells)
		error_exit("config file needs a PATTERN section or a random= line");
	else if (start >= 0 && game->grid.cells)
		error_exit("config file has both random= and PATTERN, use only one");
	else if (start >= 0)
		parse_pattern(game, lines, start);
	ft_free_split(lines);
}
