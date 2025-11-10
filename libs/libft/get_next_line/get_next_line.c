/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 02:19:54 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/24 13:29:00 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_getline(int fd, char *remaining, char *buf);
static char	*gnl_getremaining(char *line);

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*line;
	char		*buf;

	buf = (char *)gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(remaining), free(buf), NULL);
	if (!buf)
		return (free(remaining), NULL);
	line = gnl_getline(fd, remaining, buf);
	free(buf);
	if (!line)
		return (NULL);
	remaining = gnl_getremaining(line);
	return (line);
}

static char	*gnl_getline(int fd, char *remaining, char *buf)
{
	ssize_t	bytes;
	char	*tmp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(remaining), NULL);
		else if (bytes == 0)
			break ;
		buf[bytes] = 0;
		if (!remaining)
			remaining = gnl_strdup("");
		tmp = remaining;
		remaining = gnl_strjoin(tmp, buf);
		free(tmp);
		if (gnl_strchr(buf, '\n'))
			break ;
	}
	return (remaining);
}

static char	*gnl_getremaining(char *line)
{
	char	*out;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i] || !line[1])
		return (NULL);
	out = gnl_substr(line, i + 1, gnl_strlen(line) - i);
	if (!out)
	{
		free(out);
		out = NULL;
	}
	line[i + 1] = 0;
	return (out);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
