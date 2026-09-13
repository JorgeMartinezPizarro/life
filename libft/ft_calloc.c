/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:25:52 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:25:52 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total;
	void	*ptr;
	size_t	i;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
