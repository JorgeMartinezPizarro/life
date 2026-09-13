/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomarti3 <jomarti3@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:31:17 by jomarti3          #+#    #+#             */
/*   Updated: 2026/09/13 15:31:17 by jomarti3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 8192
# endif

# include <stdlib.h>
# include <unistd.h>

////////////////////////////////////////////////////////////////////////////////
// get_next_line_bonus.c
//
// Description:
//
// Return the next line of the given fd. It allows reading mixed fds. NULL is
// returned if an read error happen or if BUFFER_SIZE=0.
//
// Notes:
//
// UB if the fd changed or if the file is binary.
//
char	*get_next_line(int fd);
////////////////////////////////////////////////////////////////////////////////
// get_next_line_utils_bonus.c
////////////////////////////////////////////////////////////////////////////////
// In case of s being NULL, it returns 0.
char	*gnl_strchr(const char *s, char c);
////////////////////////////////////////////////////////////////////////////////
// In case of s being NULL, it returns 0.
size_t	gnl_strlen(const char *s);
////////////////////////////////////////////////////////////////////////////////
// It frees s1 after returning the joined string created with malloc.
char	*gnl_strjoin(char *s1, char *s2);
////////////////////////////////////////////////////////////////////////////////
// It returns a char * allocated with malloc.
char	*gnl_substr(char const *s, unsigned int start, size_t len);
////////////////////////////////////////////////////////////////////////////////
// It returns a char * allocated with malloc.
char	*gnl_strdup(char *src);
////////////////////////////////////////////////////////////////////////////////

#endif