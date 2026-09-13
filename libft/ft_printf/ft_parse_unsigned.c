/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:29 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:29 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_printf_utils.h"
#include "ft_printf.h"

void	parse_size(t_fmt *fmt, int len, char *prefix)
{
	if (fmt->precision > len)
		fmt->padding = fmt->precision - len;
	fmt->prefix_len = ft_strlen(prefix);
	if (fmt->width > len + fmt->padding + fmt->prefix_len)
		fmt->pad_width = fmt->width - len - fmt->padding - fmt->prefix_len;
	if (fmt->flag_zero && fmt->precision < 0 && !fmt->flag_minus)
		fmt->pad_char = '0';
}

int	print_unsigned(t_fmt *fmt, char *prefix, char *str, int len)
{
	int	count;

	count = 0;
	if (fmt->flag_minus)
	{
		if (fmt->prefix_len)
			count += write(1, prefix, fmt->prefix_len);
		count += ft_putnchar('0', fmt->padding);
		count += write(1, str, len);
		count += ft_putnchar(' ', fmt->pad_width);
	}
	else
	{
		if (fmt->pad_char == '0' && fmt->prefix_len)
			count += write(1, prefix, fmt->prefix_len);
		count += ft_putnchar(fmt->pad_char, fmt->pad_width);
		if (!(fmt->pad_char == '0' && fmt->prefix_len) && fmt->prefix_len)
			count += write(1, prefix, fmt->prefix_len);
		count += ft_putnchar('0', fmt->padding);
		count += write(1, str, len);
	}
	return (count);
}

int	parse_unsigned(t_fmt *fmt, uintmax_t value, const char *base, char *prefix)
{
	char	*str;
	int		len;
	int		count;

	if (fmt->spec == 'p' && value == 0)
		str = ft_strdup("(nil)");
	else if (value == 0 && fmt->precision == 0)
		str = ft_strdup("");
	else
		str = ft_utoa_base(value, base);
	if (!str)
		return (0);
	len = ft_strlen(str);
	if (value == 0)
	{
		parse_size(fmt, len, "");
		count = print_unsigned(fmt, "", str, len);
	}
	else
	{
		parse_size(fmt, len, prefix);
		count = print_unsigned(fmt, prefix, str, len);
	}
	free(str);
	return (count);
}
