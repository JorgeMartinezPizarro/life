/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:21 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:21 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_putnchar(char c, int n)
{
	int	count;

	count = 0;
	while (n-- > 0)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
}
