/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:26 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:26 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int	parse_string(t_fmt *fmt, va_list *args)
{
	char	*str;
	int		len;
	int		count;

	count = 0;
	str = va_arg(*args, char *);
	if (str == NULL)
	{
		if (fmt->precision > -1 && fmt->precision < 6)
			str = "";
		else
			str = "(null)";
	}
	len = ft_strlen(str);
	if (fmt->precision >= 0 && fmt->precision < len)
		len = fmt->precision;
	if (!fmt->flag_minus && fmt->width > len)
		count += ft_putnchar(' ', fmt->width - len);
	count += write(1, str, len);
	if (fmt->flag_minus && fmt->width > len)
		count += ft_putnchar(' ', fmt->width - len);
	return (count);
}
