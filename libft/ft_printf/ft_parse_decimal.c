/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:19 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:19 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf.h"

static char	*parse_sign(t_fmt *fmt, va_list *args, char *sign, int *value)
{
	char			*str;
	unsigned long	uvalue;

	*sign = 0;
	*value = va_arg(*args, int);
	if (*value < 0)
	{
		*sign = '-';
		uvalue = (unsigned long)(-(long)(*value));
	}
	else
	{
		if (fmt->flag_plus)
			*sign = '+';
		else if (fmt->flag_space)
			*sign = ' ';
		uvalue = (unsigned long)(*value);
	}
	str = ft_utoa_base(uvalue, "0123456789");
	return (str);
}

static int	parse_padding(t_fmt *fmt, int len, int value)
{
	int	total_len;

	if (fmt->precision == 0 && value == 0)
		len = 0;
	if (fmt->precision > len)
		fmt->padding = fmt->precision - len;
	total_len = len + fmt->padding;
	if (fmt->sign)
		total_len += 1;
	if (fmt->width > total_len)
		fmt->pad_width = fmt->width - total_len;
	if (fmt->flag_zero && fmt->precision < 0 && !fmt->flag_minus)
		fmt->pad_char = '0';
	return (len);
}

int	print_negative(t_fmt *fmt, char *str, int len)
{
	int	count;

	count = 0;
	if (fmt->sign)
		count += write(1, &(fmt->sign), 1);
	count += ft_putnchar('0', fmt->padding);
	count += write(1, str, len);
	count += ft_putnchar(' ', fmt->pad_width);
	return (count);
}

int	print_positive(t_fmt *fmt, char *str, int len)
{
	int	count;

	count = 0;
	if (fmt->pad_char == '0')
	{
		if (fmt->sign)
			count += write(1, &(fmt->sign), 1);
		count += ft_putnchar('0', fmt->pad_width);
	}
	else
	{
		count += ft_putnchar(' ', fmt->pad_width);
		if (fmt->sign)
			count += write(1, &(fmt->sign), 1);
	}
	count += ft_putnchar('0', fmt->padding);
	count += write(1, str, len);
	return (count);
}

int	parse_decimal(t_fmt *fmt, va_list *args)
{
	int		value;
	int		count;
	char	*str;
	int		len;

	count = 0;
	str = parse_sign(fmt, args, &(fmt->sign), &value);
	if (!str)
		return (0);
	len = ft_strlen(str);
	len = parse_padding(fmt, len, value);
	if (fmt->flag_minus)
		count += print_negative(fmt, str, len);
	else
		count += print_positive(fmt, str, len);
	free(str);
	return (count);
}
