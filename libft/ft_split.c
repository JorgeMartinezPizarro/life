/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:31 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:31 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*word_dup(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

static void	free_all(char **res, int i)
{
	while (i-- > 0)
		free(res[i]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		start;
	int		end;
	int		i;

	if (s)
		res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !res)
		return (NULL);
	i = 0;
	end = 0;
	while (s[end])
	{
		while (s[end] == c && s[end])
			end++;
		start = end;
		while (s[end] && s[end] != c)
			end++;
		if (end > start)
			res[i++] = word_dup(s, start, end);
		if (i > 0 && !res[i - 1])
			return (free_all(res, i), NULL);
	}
	res[i] = NULL;
	return (res);
}
