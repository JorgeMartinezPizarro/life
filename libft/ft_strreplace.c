/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:30:28 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:30:28 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_occur(const char *s, const char *a)
{
	size_t	count;
	size_t	len_a;

	if (!*a)
		return (0);
	count = 0;
	len_a = ft_strlen(a);
	s = ft_strnstr(s, a, ft_strlen(s));
	while (s)
	{
		count++;
		s += len_a;
		s = ft_strnstr(s, a, ft_strlen(s));
	}
	return (count);
}

static size_t	final_len(const char *s, const char *a, const char *b)
{
	size_t	n;
	size_t	la;
	size_t	lb;

	la = ft_strlen(a);
	lb = ft_strlen(b);
	n = count_occur(s, a);
	return (ft_strlen(s) + n * (lb - la));
}

static void	replace_copy(const char **s, size_t la,
				const char *b, char **p)
{
	ft_memcpy(*p, b, ft_strlen(b));
	*p += ft_strlen(b);
	*s += la;
}

char	*ft_strreplace(const char *s, const char *a, const char *b)
{
	char	*r;
	size_t	la;
	char	*p;

	if (!s || !a || !b)
		return (NULL);
	la = ft_strlen(a);
	if (la == 0)
		return (ft_strdup(s));
	r = malloc(final_len(s, a, b) + 1);
	if (!r)
		return (NULL);
	p = r;
	while (*s)
	{
		if (ft_strnstr(s, a, la) == s)
			replace_copy(&s, la, b, &p);
		else
			*p++ = *s++;
	}
	*p = '\0';
	return (r);
}
