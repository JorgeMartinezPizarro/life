/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:31:02 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:31:02 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_utils.h"
#include <stdlib.h>

char	*ft_utoa_base(uintmax_t number, const char *base)
{
	size_t		len;
	char		buf[65];
	size_t		i;
	char		*res;
	size_t		j;

	if (!is_valid_base(base))
		return (NULL);
	len = ft_strlen((char *)base);
	i = 0;
	if (number == 0)
		return (ft_strdup("0"));
	while (number != 0)
	{
		buf[i++] = base[number % len];
		number /= len;
	}
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (i-- > 0)
		res[j++] = buf[i];
	res[j] = '\0';
	return (res);
}
