/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:18 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:18 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int nb, int fd)
{
	char	c[20];
	int		j;
	long	aux;

	aux = (long)nb;
	if (aux == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (aux < 0)
	{
		write(fd, "-", 1);
		aux = -aux;
	}
	j = 0;
	while (aux > 0)
	{
		c[j++] = '0' + (aux % 10);
		aux = aux / 10;
	}
	while (j > 0)
	{
		write(fd, &c[--j], 1);
	}
}
