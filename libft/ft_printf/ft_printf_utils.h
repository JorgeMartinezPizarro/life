/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:28:33 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:28:33 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# include <stdarg.h>
# include <stdint.h>

typedef struct s_fmt
{
	int		width;
	int		precision;
	char	flag_minus;
	char	flag_plus;
	char	flag_zero;
	char	flag_hash;
	char	flag_space;
	char	spec;
	//
	int		padding;
	int		pad_width;
	char	sign;
	char	pad_char;
	int		prefix_len;
}		t_fmt;

int			parse_unsigned(
				t_fmt *fmt, uintmax_t value, const char *base, char *prefix);
int			parse_string(t_fmt *fmt, va_list *args);
int			parse_decimal(t_fmt *fmt, va_list *args);
int			parse_char(t_fmt *fmt, va_list *args);
const char	*parse_format(const char *fmt, t_fmt *f, va_list *args);
int			dispatch_format(t_fmt *fmt, va_list *args);

int			ft_putnchar(char c, int n);
int			is_valid_base(const char *base);
// Public interes helpers
char		*ft_itoa_base(int nb, const char *base);
char		*ft_utoa_base(uintmax_t number, const char *base);

#endif