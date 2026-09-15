/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fields.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 14:33:39 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/15 14:33:46 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

char	*num_field(char *label, int value)
{
	char	*num;
	char	*labeled;
	char	*out;

	num = ft_itoa(value);
	labeled = ft_strjoin(label, num);
	free(num);
	out = ft_strjoin(labeled, "  ");
	free(labeled);
	return (out);
}

char	*str_field(char *label, char *value)
{
	char	*labeled;
	char	*out;

	labeled = ft_strjoin(label, value);
	out = ft_strjoin(labeled, "  ");
	free(labeled);
	return (out);
}

char	*append(char *acc, char *piece)
{
	char	*out;

	out = ft_strjoin(acc, piece);
	free(acc);
	free(piece);
	return (out);
}

char	*rule_label(t_rule *rule)
{
	char	buf[24];
	int		i;
	int		n;

	n = 0;
	buf[n++] = 'B';
	i = 0;
	while (i < 9)
	{
		if (rule->born[i])
			buf[n++] = '0' + i;
		i++;
	}
	buf[n++] = '/';
	buf[n++] = 'S';
	i = 0;
	while (i < 9)
	{
		if (rule->survive[i])
			buf[n++] = '0' + i;
		i++;
	}
	buf[n] = '\0';
	return (ft_strdup(buf));
}
