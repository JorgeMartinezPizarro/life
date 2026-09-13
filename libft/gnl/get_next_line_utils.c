/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:31:11 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:31:11 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s2)
		return (s1);
	if (!s1)
		return (gnl_strdup(s2));
	new = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1 && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (s2[i])
		new[j++] = s2[i++];
	new[j] = '\0';
	free(s1);
	return (new);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = gnl_strlen(s);
	if (start >= s_len)
		len = 0;
	else if (len > s_len - start)
		len = s_len - start;
	sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*gnl_strdup(char *src)
{
	size_t		size;
	size_t		i;
	char		*res;

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
