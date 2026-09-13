/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:25:56 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:25:56 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf_utils.h"

static uintmax_t	get_uint(va_list *args)
{
	return ((uintmax_t)va_arg(*args, unsigned int));
}

static uintmax_t	get_ptr(va_list *args)
{
	return ((uintmax_t)(uintptr_t)va_arg(*args, void *));
}

int	dispatch_format(t_fmt *fmt, va_list *args)
{
	int	count;

	count = 0;
	if (fmt->spec == 'd' || fmt->spec == 'i')
		count += parse_decimal(fmt, args);
	else if (fmt->spec == 's')
		count += parse_string(fmt, args);
	else if (fmt->spec == 'c')
		count += parse_char(fmt, args);
	else if (fmt->spec == 'u')
		count += parse_unsigned(fmt, get_uint(args), "0123456789", "");
	else if (fmt->spec == 'x' && fmt->flag_hash)
		count += parse_unsigned(fmt, get_uint(args), "0123456789abcdef", "0x");
	else if (fmt->spec == 'x')
		count += parse_unsigned(fmt, get_uint(args), "0123456789abcdef", "");
	else if (fmt->spec == 'X' && fmt->flag_hash)
		count += parse_unsigned(fmt, get_uint(args), "0123456789ABCDEF", "0X");
	else if (fmt->spec == 'X')
		count += parse_unsigned(fmt, get_uint(args), "0123456789ABCDEF", "");
	else if (fmt->spec == 'p')
		count += parse_unsigned(fmt, get_ptr(args), "0123456789abcdef", "0x");
	else if (fmt->spec == '%')
		count += write(1, "%", 1);
	return (count);
}
