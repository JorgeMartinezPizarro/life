/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:13 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:13 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *dest, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*destiny;
	size_t			i;

	destiny = (unsigned char *)dest;
	uc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		destiny[i] = uc;
		i++;
	}
	return (dest);
}
