/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:29:28 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:29:28 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static void	read_all(int fd, char *content, size_t size)
{
	ssize_t	r;
	size_t	total;

	total = 0;
	r = read(fd, content + total, size - total);
	while (r > 0 && total < size)
	{
		total += (size_t)r;
		r = read(fd, content + total, size - total);
	}
	content[total] = '\0';
}

char	*ft_read_file(char *path)
{
	int			fd;
	struct stat	st;
	char		*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (fstat(fd, &st) < 0 || st.st_size < 0)
	{
		close(fd);
		return (NULL);
	}
	content = malloc((size_t)st.st_size + 1);
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	read_all(fd, content, (size_t)st.st_size);
	close(fd);
	return (content);
}
