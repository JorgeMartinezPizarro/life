/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:30:14 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:30:14 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			slen;
	unsigned int	i;
	char			*ret;

	if (!s)
		return (NULL);
	slen = 0;
	while (s[slen] != 0)
		slen++;
	ret = malloc(slen + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		ret[i] = f(i, s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
