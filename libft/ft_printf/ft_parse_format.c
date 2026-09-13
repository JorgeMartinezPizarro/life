/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:23 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:23 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_utils.h"
#include "ft_printf.h"

const char	*parse_flags(const char *fmt, t_fmt *f)
{
	while (ft_strchr("-0# +", *fmt))
	{
		if (*fmt == '-')
			f->flag_minus = 1;
		if (*fmt == '+')
			f->flag_plus = 1;
		if (*fmt == '0')
			f->flag_zero = 1;
		if (*fmt == '#')
			f->flag_hash = 1;
		if (*fmt == ' ')
			f->flag_space = 1;
		fmt++;
	}
	return (fmt);
}

const char	*parse_width(const char *fmt, t_fmt *f, va_list *args)
{
	if (*fmt == '*')
	{
		fmt++;
		f->width = va_arg(*args, int);
		if (f->width < 0)
		{
			f->flag_minus = 1;
			f->width = -f->width;
		}
	}
	else if (*fmt >= '0' && *fmt <= '9')
	{
		f->width = ft_atoi(fmt);
		while (*fmt >= '0' && *fmt <= '9')
			fmt++;
	}
	return (fmt);
}

const char	*parse_precision(const char *fmt, t_fmt *f, va_list *args)
{
	f->precision = -1;
	if (*fmt == '.')
	{
		fmt++;
		if (*fmt == '*')
		{
			fmt++;
			f->precision = va_arg(*args, int);
		}
		else
		{
			f->precision = ft_atoi(fmt);
			if (*fmt == '-')
				fmt++;
			while (*fmt >= '0' && *fmt <= '9')
				fmt++;
		}
	}
	if (f->precision < 0)
		f->precision = -1;
	return (fmt);
}

const char	*parse_format(const char *fmt, t_fmt *f, va_list *args)
{
	fmt = parse_flags(fmt, f);
	fmt = parse_width(fmt, f, args);
	fmt = parse_precision(fmt, f, args);
	f->spec = *fmt;
	if (!ft_strchr("%disxXupc", f->spec))
		f->spec = 0;
	if (f->spec != 0)
		fmt++;
	return (fmt);
}
