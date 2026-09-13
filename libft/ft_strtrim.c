/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:30:36 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:30:36 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

static int	contained(char c, const char *set)
{
	size_t	leng;

	leng = 0;
	while (set[leng] != 0)
	{
		if (set[leng] == c)
			return (1);
		leng++;
	}
	return (0);
}

static char	*empty(void)
{
	char	*ret;

	ret = malloc(1);
	if (!ret)
		return (NULL);
	ret[0] = '\0';
	return (ret);
}

static void	get_bounds(const char *s, const char *set, size_t *bounds)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	bounds[0] = 0;
	while (bounds[0] < len && contained(s[bounds[0]], set))
		bounds[0]++;
	bounds[1] = len;
	while (bounds[1] > bounds[0] && contained(s[bounds[1] - 1], set))
		bounds[1]--;
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	bounds[2];
	char	*ret;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	get_bounds(s1, set, bounds);
	if (bounds[0] >= bounds[1])
		return (empty());
	ret = malloc(bounds[1] - bounds[0] + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (bounds[0] < bounds[1])
		ret[i++] = s1[bounds[0]++];
	ret[i] = '\0';
	return (ret);
}
