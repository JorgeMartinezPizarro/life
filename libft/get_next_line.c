/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:31:14 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:31:14 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buffer_read(int fd, char *buf, char *tmp)
{
	ssize_t	r;

	r = 1;
	while (!gnl_strchr(buf, '\n') && r > 0)
	{
		r = read(fd, tmp, BUFFER_SIZE);
		if (r < 0)
		{
			free(buf);
			return (NULL);
		}
		if (r == 0)
			break ;
		tmp[r] = '\0';
		buf = gnl_strjoin(buf, tmp);
		if (!buf)
			return (NULL);
	}
	return (buf);
}

static char	*get_line(char *buf)
{
	char	*nl;
	size_t	len;

	if (!buf || !*buf)
		return (NULL);
	nl = gnl_strchr(buf, '\n');
	if (nl)
		len = nl - buf + 1;
	else
		len = gnl_strlen(buf);
	return (gnl_substr(buf, 0, len));
}

static char	*get_remainder(char *buf)
{
	char	*nl;
	char	*rest;

	if (!buf)
		return (NULL);
	nl = gnl_strchr(buf, '\n');
	if (!nl || !*(nl + 1))
	{
		free(buf);
		return (NULL);
	}
	rest = gnl_substr(buf, nl - buf + 1, gnl_strlen(nl + 1));
	free(buf);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buf[OPEN_MAX] = {NULL};
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	if (!buf[fd])
		buf[fd] = gnl_strdup("");
	buf[fd] = buffer_read(fd, buf[fd], tmp);
	free(tmp);
	line = get_line(buf[fd]);
	buf[fd] = get_remainder(buf[fd]);
	return (line);
}
