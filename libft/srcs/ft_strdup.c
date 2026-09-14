/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:42 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:42 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

char	*ft_strdup(const char *src)
{
	size_t	size;
	size_t	i;
	char	*res;

	size = 0;
	while (src[size] != 0)
		size++;
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = src[i];
		i++;
	}
	res[size] = 0;
	return (res);
}
