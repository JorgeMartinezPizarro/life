/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_valid_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:31:07 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:31:07 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

int	ft_valid_int(const char *str)
{
	long	val;
	int		sign;

	val = 0;
	sign = 1;
	if (!str || !*str)
		return (0);
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		val = val * 10 + (*str - '0');
		if ((sign == 1 && val > INT_MAX) || (sign == -1 && (-val) < INT_MIN))
			return (0);
		str++;
	}
	return (1);
}
