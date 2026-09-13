/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:30:41 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:30:41 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	get_sub_len(const char *s, unsigned int start, size_t len)
{
	size_t	leng;

	leng = 0;
	while (s[leng])
		leng++;
	if (start >= leng)
		return (0);
	if (len > leng - start)
		len = leng - start;
	return (len);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sub_len;
	char	*ret;

	if (!s)
		return (NULL);
	sub_len = get_sub_len(s, start, len);
	ret = malloc(sub_len + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < sub_len)
	{
		ret[i] = s[start + i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
