/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:59 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:59 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "ft_printf_utils.h"

static t_fmt	new_format(void)
{
	t_fmt	fmt;

	fmt.width = 0;
	fmt.precision = -1;
	fmt.flag_minus = 0;
	fmt.flag_plus = 0;
	fmt.flag_zero = 0;
	fmt.flag_hash = 0;
	fmt.flag_space = 0;
	fmt.spec = 0;
	fmt.padding = 0;
	fmt.pad_width = 0;
	fmt.sign = 0;
	fmt.pad_char = ' ';
	fmt.prefix_len = 0;
	return (fmt);
}

static const char	*handle_format(
	const char *format, va_list *args, int *count)
{
	t_fmt	fmt;

	fmt = new_format();
	format = parse_format(format, &fmt, args);
	if (fmt.spec)
		*count += dispatch_format(&fmt, args);
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format)
				format = handle_format(format, &args, &count);
		}
		else
		{
			write(1, format, 1);
			count++;
			format++;
		}
	}
	va_end(args);
	return (count);
}
