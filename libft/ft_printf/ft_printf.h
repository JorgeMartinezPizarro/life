/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:02 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:02 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <string.h>

////////////////////////////////////////////////////////////////////////////////
// ft_printf.c
//
// Description:
//
// ft_printf replicates the behavior of the standard printf function for the
// following format specifiers: d, i, u, p, s, c, x, X, and %.
//
// Supported flags and modifiers:
//
//  - space, precision, width, wildcards (*), minus (-), plus (+), hash (#)
//
// Special design choices:
//
//  - Null pointers are represented as (nil). Width and precision are applied,
//    and cutting off results in nothing printed.
//
//  - NULL strings are treated as "(null)". Width and precision are applied
//    as if it were a normal string. If truncated, nothing is printed.
//
//  - Invalid or incomplete format specifiers are ignored. A '%' followed by
//    an unrecognized specifier may cause UB.
//
//  - Wildcards with NULL value always generate UB.
////////////////////////////////////////////////////////////////////////////////
int			ft_printf(char const *format, ...);

#endif