/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:49 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:49 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*join;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = malloc(s1len + s2len + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		join[s1len + i] = s2[i];
		i++;
	}
	join[s1len + i] = '\0';
	return (join);
}
