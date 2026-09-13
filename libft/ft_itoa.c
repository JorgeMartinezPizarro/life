/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:27:12 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:27:12 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char	*to_ascii(long long n, int len, int sign)
{
	char	*str;
	int		i;

	i = len - 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (i >= 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
	if (sign < 0)
		str[0] = '-';
	return (str);
}

static char	*ft_zero(void)
{
	char	*ret;

	ret = malloc(2);
	if (!ret)
		return (NULL);
	ret[0] = '0';
	ret[1] = 0;
	return (ret);
}

char	*ft_itoa(int num)
{
	long long	n;
	int			len;
	long long	tmp;
	int			sign;

	len = 0;
	n = (long long)num;
	sign = 1;
	if (n == 0)
		return (ft_zero());
	if (n < 0)
		sign = -1;
	if (sign < 0)
		n = -n;
	tmp = n;
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	if (sign < 0)
		len++;
	return (to_ascii(n, len, sign));
}
