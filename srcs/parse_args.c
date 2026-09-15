/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:36 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:36 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static int	is_flag(char *arg)
{
	return (arg[0] == '-' && arg[1] == '-');
}

static char	*derive_title(char *path)
{
	char	*base;
	char	*dot;
	size_t	len;

	base = ft_strrchr(path, '/');
	if (base)
		base++;
	else
		base = path;
	dot = ft_strrchr(base, '.');
	if (dot && dot != base)
		len = (size_t)(dot - base);
	else
		len = ft_strlen(base);
	return (ft_substr(base, 0, len));
}

static void	apply_flag(t_game *game, char *arg)
{
	char	*msg;

	msg = NULL;
	if (!ft_strncmp(arg, "--rule=", 7))
		msg = parse_rule(&game->rule, arg + 7);
	else if (!ft_strncmp(arg, "--random=", 9))
		msg = parse_random(game, arg + 9);
	else if (!ft_strncmp(arg, "--speed=", 8))
		game->speed_ms = ft_atoi(arg + 8);
	else if (!ft_strncmp(arg, "--cell=", 7))
		game->cell_size = ft_atoi(arg + 7);
	else if (!ft_strncmp(arg, "--edge=", 7))
		msg = apply_edge(game, arg + 7);
	else
		usage_exit();
	if (msg)
		error_exit(msg);
}

void	parse_args(t_game *game, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_flag(argv[i]))
			apply_flag(game, argv[i]);
		else if (!game->grid.cells)
		{
			free(game->title);
			game->title = derive_title(argv[i]);
			parse_config(game, argv[i]);
		}
		else
			usage_exit();
		i++;
	}
}
