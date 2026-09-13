/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rule.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:34:55 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:34:55 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "life.h"

static void	parse_digits(char *str, int *arr)
{
	int	i;
	int	n;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || str[i] - '0' > 8)
			error_exit("invalid rule: digits must be 0-8");
		n = str[i] - '0';
		arr[n] = 1;
		i++;
	}
}

void	parse_rule(t_rule *rule, char *str)
{
	char	**parts;

	ft_memset(rule->born, 0, sizeof(rule->born));
	ft_memset(rule->survive, 0, sizeof(rule->survive));
	parts = ft_split(str, '/');
	if (!parts || !parts[0] || !parts[1] || parts[2])
		error_exit("invalid rule format, expected Bxxx/Sxxx e.g. B3/S23");
	if (parts[0][0] != 'B' && parts[0][0] != 'b')
		error_exit("invalid rule: first part must start with B");
	if (parts[1][0] != 'S' && parts[1][0] != 's')
		error_exit("invalid rule: second part must start with S");
	parse_digits(parts[0] + 1, rule->born);
	parse_digits(parts[1] + 1, rule->survive);
	ft_free_split(parts);
}
