/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_random.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:51 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:51 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	seed_random(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	srand((unsigned int)(tv.tv_sec ^ tv.tv_usec));
}

static void	randomize_grid(t_grid *grid, int percent)
{
	int	i;

	i = 0;
	while (i < grid->width * grid->height)
	{
		if ((rand() % 100) < percent)
			grid->cells[i] = 1;
		i++;
	}
}

void	parse_random(t_game *game, char *value)
{
	char	**wh;
	char	**hp;
	int		width;
	int		height;
	int		percent;

	wh = ft_split(value, 'x');
	if (!wh || !wh[0] || !wh[1] || wh[2])
		error_exit("invalid --random format, expected WxH:PERCENT");
	hp = ft_split(wh[1], ':');
	if (!hp || !hp[0] || !hp[1] || hp[2])
		error_exit("invalid --random format, expected WxH:PERCENT");
	width = ft_atoi(wh[0]);
	height = ft_atoi(hp[0]);
	percent = ft_atoi(hp[1]);
	ft_free_split(wh);
	ft_free_split(hp);
	if (width <= 0 || height <= 0 || percent < 0 || percent > 100)
		error_exit("invalid --random values");
	if (width > MAX_GRID_WIDTH || height > MAX_GRID_HEIGHT)
		error_exit("--random dimensions exceed maximum allowed size");
	grid_alloc(&game->grid, width, height);
	seed_random();
	randomize_grid(&game->grid, percent);
}
