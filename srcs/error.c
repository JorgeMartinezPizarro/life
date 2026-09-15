/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:10 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:10 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("life: error: ", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}

int	safe_len(size_t n)
{
	if (n > MAX_STR_LEN)
		error_exit("value too large: exceeds MAX_STR_LEN");
	return ((int)n);
}

void	usage_exit(void)
{
	ft_putendl_fd("", 2);
	ft_putendl_fd(" usage: ./life <config_file> [options]", 2);
	ft_putendl_fd("   or: ./life --random=WxH:PERCENT [options]", 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd(" options:", 2);
	ft_putendl_fd("  --rule=Bxxx/Sxxx    life-like rule, e.g. B3/S23", 2);
	ft_putendl_fd("  --random=WxH:PCT    random grid, PCT chance alive", 2);
	ft_putendl_fd("  --speed=ms          generation interval in ms", 2);
	ft_putendl_fd("  --cell=px           pixel size of one cell", 2);
	ft_putendl_fd("  --edge=MODE  finite|cylinder|torus|mobius|klein|projective", 2);
	ft_putendl_fd("", 2);
	ft_putendl_fd(" keys: ESC quit | SPACE pause | N step | R reset", 2);
	ft_putendl_fd("", 2);
	exit(1);
}
