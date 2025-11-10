/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:50:25 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/11 02:24:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

// main file
char	*get_next_line(int fd);

// utils file
size_t	gnl_strlen(const char *s);
void	*gnl_calloc(size_t nmemb, size_t size);
char	*gnl_substr(const char *s, unsigned int start, size_t len);
char	*gnl_strjoin(const char *s1, const char *s2);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strdup(const char *s);

#endif