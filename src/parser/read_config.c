/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:27:01 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:41:54 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*file_to_string(int fd, ssize_t bread)
{
	char	buf[1024];
	char	*out;
	char	*tmp;

	if (fd == -1)
		return (NULL);
	out = ft_strdup("");
	if (!out)
		return (close(fd), NULL);
	while (bread > 0)
	{
		ft_bzero(buf, 1024);
		bread = read(fd, buf, 1023);
		if (bread == 0)
			break ;
		else if (bread == -1)
			return (close(fd), free(out), NULL);
		tmp = out;
		out = ft_strjoin(out, buf);
		free(tmp);
		if (!out)
			return (close(fd), NULL);
	}
	close(fd);
	return (out);
}

static size_t	config_linecount(char *s)
{
	size_t	i;
	size_t	lines;

	i = 0;
	lines = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			lines++;
		i++;
	}
	return (lines + 1);
}

static char	**config_split(char *oneline, size_t lines)
{
	char	**out;
	char	*ptr;
	ssize_t	i;
	ssize_t	j;

	out = ft_calloc(lines + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = -1;
	ptr = oneline;
	while (ptr && ptr[0])
	{
		j = 0;
		while (ptr[++j] && ptr[j] != '\n')
			;
		if (ptr[j] && ptr[j + 1])
			j++;
		out[++i] = ft_strndup(ptr, j);
		if (!out[i])
			return (free_split(out), NULL);
		if (!ft_strchr(ptr, '\n'))
			break ;
		ptr = ft_strchr(ptr + 1, '\n');
	}
	return ((out[lines] = NULL), out);
}

static char	**config_cleanup(char **in, size_t lines)
{
	ssize_t	i;
	char	**out;

	if (!in)
		return (NULL);
	out = ft_calloc(lines + 1, sizeof(char *));
	if (!out)
		return (free_split(in), NULL);
	i = -1;
	while (i < (ssize_t)lines && in[++i])
	{
		out[i] = ft_strtrim(in[i], "\n");
		if (!out[i])
			return (free_split(out), free_split(in), NULL);
	}
	free_split(in);
	return (out);
}

void	read_config(t_data *data, char *file)
{
	char	*oneline;
	size_t	lc;

	oneline = file_to_string(open(file, O_RDONLY), 1);
	if (!oneline)
		error_exit("read_config", data);
	lc = config_linecount(oneline);
	if (!lc)
	{
		free(oneline);
		error_exit("config is empty", data);
	}
	data->config.raw_config = config_split(oneline, lc);
	free(oneline);
	data->config.raw_config = config_cleanup(data->config.raw_config, lc);
	if (!data->config.raw_config)
		error_exit("malloc failed", data);
}
