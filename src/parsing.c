/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:14:22 by dvavryn           #+#    #+#             */
/*   Updated: 2025/11/11 01:32:30 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	argcheck(int argc, char **argv)
{
	size_t	len;

	if (argc < 2)
		error_exit("filename missing", NULL);
	else if (argc > 2)
		error_exit("Usage: ./cub3d file.cub", NULL);
	len = ft_strlen(argv[1]);
	if (!len)
		error_exit("empty filename", NULL);
	else if (len <= 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		error_exit("invalid file extension. expected '.cub'", NULL);
}

char	*file_to_string(int fd, ssize_t bread)
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

size_t	config_linecount(char	*s)
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
	if (i == 0 || s[i - 1] == '\n')
		return (lines);
	else
		return (lines + 1);
}

char	**config_split(char *oneline, size_t lines)
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
		ptr = ft_strchr(ptr, '\n') + 1;
	}
	return (out);
}

char	**config_cleanup(char **in, size_t lines)
{
	ssize_t	i;
	char	**out;

	if (!in)
		return (NULL);
	out = ft_calloc(lines + 1, sizeof(char *));
	if (!out)
		return (free_split(in), NULL);
	i = -1;
	while (in[++i])
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
		error_exit(strerror(errno), data);
	lc = config_linecount(oneline);
	if (!lc)
	{
		free(oneline);
		error_exit("config is empty", data);
	}
	data->config.raw_config = config_split(oneline, lc);						// if line before empty, duplicates line -> results in double NO, dobule F and double first line of map
	free(oneline);
	data->config.raw_config = config_cleanup(data->config.raw_config, lc);
	if (!data->config.raw_config)
		error_exit("malloc failed", data);
}

void	get_config(t_data *data, ssize_t i)
{
	char	*ptr;
	char	*buf;

	while (data->config.raw_config[i] && (!data->config.raw_config[i][0]
		|| !ft_strchr(" \t01", data->config.raw_config[i][0])))
	{
		ptr = data->config.raw_config[i];
		buf = ft_strdup(ptr);
		if (!buf)
			error_exit("malloc failed", data);
		if (!ft_strncmp("NO ", ptr, 3))
			data->config.north_texture = buf;		// leaking
		else if (!ft_strncmp("EA ", ptr, 3))
			data->config.east_texture = buf;
		else if (!ft_strncmp("SO ", ptr, 3))
			data->config.south_texture = buf;
		else if (!ft_strncmp("WE ", ptr, 3))
			data->config.west_texture = buf;
		else if (!ft_strncmp("F ", ptr, 2))
			data->config.floor_color = buf;			// leaking
		else if (!ft_strncmp("C ", ptr, 2))
			data->config.ceiling_color = buf;
		else
			free(buf);
		buf = NULL;
		i++;
	}
}

size_t	get_map_size(char **config)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (config[i] && !ft_strchr(" \t 01", config[i][0]))
		i++;
	while (config[j])
		j++;
	return (j - i);
}

void	extract_map(t_data *data)
{
	size_t	i;
	ssize_t	j;
	char	**out;

	out = ft_calloc(get_map_size(data->config.raw_config) + 1, sizeof(char *));
	if (!out)
		error_exit("malloc failed", data);
	i = 0;
	while (data->config.raw_config[i] && (!data->config.raw_config[i][0]
		|| !ft_strchr(" \t01", data->config.raw_config[i][0])))
		i++;
	j = -1;
	while (data->config.raw_config[i])
	{
		out[++j] = ft_strdup(data->config.raw_config[i]);
		if (!out[j])
		{
			free_split(out);
			error_exit("malloc failed", data);
		}
		i++;
	}
	free_split(data->config.raw_config);
	data->config.raw_config = out;
}

void	check_chars(t_data *data, char **map)
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(" \t01NSEW", map[i][j]))
				error_exit("invalid character inside of map", data);
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (data->config.player_orientation)
					error_exit("invalid amount of starting positions", data);
				data->config.player_position_x = j;
				data->config.player_position_y = i;
				data->config.player_orientation = map[i][j];
				map[i][j] = '0';
			}
		}
	}
}

size_t	get_size_map(char **config, char c)
{
	size_t	out;
	size_t	i;
	out = 0;
	if (c == 'l')
	{
		i = 0;
		while (config[i])
		{
			if (ft_strlen(config[i]) > out)
				out = ft_strlen(config[i]);
			i++;
		}
	}
	else
	{
		while (config[out])
			out++;
	}
	return (out);
}

void	alloc_map(t_data *data, char **config)
{
	size_t	i;

	data->map.map_x = get_size_map(config, 'l');
	data->map.map_y = get_size_map(config, 'h');
	data->map.map = ft_calloc(data->map.map_y + 1, sizeof(int *));
	if (!data->map.map)
		error_exit("malloc failed", data);
	i = 0;
	while (i < data->map.map_y)
	{
		data->map.map[i] = ft_calloc(data->map.map_x, sizeof(int));
		if (!data->map.map[i])
			error_exit("malloc failed", data);
		i++;
	}
}

void	convert_map(t_data *data, char **con)
{
	size_t	i;
	size_t	j;
	int		**map;

	map = data->map.map;
	i = 0;
	while (con[i])
	{
		j = 0;
		while (con[i][j])
		{
			if (con[i][j] == ' ')
				map[i][j] = -1;
			else if (con[i][j] == '1')
				map[i][j] = 1;
			j++;
		}
		while (j < data->map.map_x)
		{
			map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	validate_map(t_data *data)
{
	check_chars(data, data->config.raw_config);
	alloc_map(data, data->config.raw_config);
	convert_map(data, data->config.raw_config);
}

void	parsing(t_data *data, int argc, char **argv)
{
	ft_bzero(data, sizeof(t_data));
	argcheck(argc, argv);
	read_config(data, argv[1]);
	get_config(data, 0);
	if (!data->config.north_texture || !data->config.east_texture
		|| !data->config.south_texture || !data->config.west_texture)
		error_exit("textures missing", data);
	if (!data->config.floor_color || !data->config.ceiling_color)
		error_exit("colors missing", data);
	extract_map(data);
	validate_map(data);
}
