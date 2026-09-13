/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:45 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:45 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t			slen;
	unsigned int	i;

	if (!s)
		return ;
	slen = 0;
	while (s[slen] != 0)
		slen++;
	i = 0;
	while (i < slen)
	{
		f(i, &s[i]);
		i++;
	}
}
