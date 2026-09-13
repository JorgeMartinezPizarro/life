/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:25:48 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:25:48 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *b, size_t len)
{
	unsigned char	*zeros;
	size_t			i;

	i = 0;
	zeros = (unsigned char *)b;
	while (i < len)
	{
		zeros[i] = 0;
		i++;
	}
}
