/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:27:08 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:27:08 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <stdlib.h>

static unsigned long	get_unsigned(int nb, int *is_negative)
{
	*is_negative = (nb < 0);
	if (*is_negative)
		return ((unsigned long)(-(long)nb));
	return ((unsigned long)nb);
}

static char	*build_negative(char *temp)
{
	char	*res;
	size_t	i;

	res = malloc(ft_strlen(temp) + 2);
	if (!res)
	{
		free(temp);
		return (NULL);
	}
	res[0] = '-';
	i = 0;
	while (temp[i])
	{
		res[i + 1] = temp[i];
		i++;
	}
	res[i + 1] = '\0';
	free(temp);
	return (res);
}

char	*ft_itoa_base(int nb, const char *base)
{
	char			*temp;
	unsigned long	number;
	int				is_negative;

	if (!is_valid_base(base))
		return (NULL);
	number = get_unsigned(nb, &is_negative);
	temp = ft_utoa_base(number, base);
	if (!temp)
		return (NULL);
	if (!is_negative)
		return (temp);
	return (build_negative(temp));
}
