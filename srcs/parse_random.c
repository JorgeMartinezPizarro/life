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

static char	*split_dims(char *value, int *width, int *height, int *percent)
{
	char	**wh;
	char	**hp;

	wh = ft_split(value, 'x');
	if (!wh || !wh[0] || !wh[1] || wh[2])
	{
		if (wh)
			ft_free_split(wh);
		return ("invalid --random format, expected WxH:PERCENT");
	}
	hp = ft_split(wh[1], ':');
	if (!hp || !hp[0] || !hp[1] || hp[2])
	{
		ft_free_split(wh);
		if (hp)
			ft_free_split(hp);
		return ("invalid --random format, expected WxH:PERCENT");
	}
	*width = ft_atoi(wh[0]);
	*height = ft_atoi(hp[0]);
	*percent = ft_atoi(hp[1]);
	ft_free_split(wh);
	ft_free_split(hp);
	return (NULL);
}

char	*parse_random(t_game *game, char *value)
{
	int		width;
	int		height;
	int		percent;
	char	*msg;

	msg = split_dims(value, &width, &height, &percent);
	if (msg)
		return (msg);
	if (width <= 0 || height <= 0 || percent < 0 || percent > 100)
		return ("invalid --random values");
	if (width > MAX_GRID_WIDTH || height > MAX_GRID_HEIGHT)
		return ("--random dimensions exceed maximum allowed size");
	grid_alloc(&game->grid, width, height);
	seed_random();
	randomize_grid(&game->grid, percent);
	return (NULL);
}
