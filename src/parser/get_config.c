/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:31:19 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/18 14:54:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_text_path(t_data *data, char *buf)
{
	char	*out;

	out = ft_strtrim(buf + 3, " ");
	free(buf);
	if (!out)
		error_exit("malloc failed", data);
	return (out);
}

int	is_config(char *s)
{
	if (!ft_strncmp("NO", s, 2) && (s[2] == 0 || s[2] == ' '))
		return (1);
	else if (!ft_strncmp("EA", s, 2) && (s[2] == 0 || s[2] == ' '))
		return (1);
	else if (!ft_strncmp("SO", s, 2) && (s[2] == 0 || s[2] == ' '))
		return (1);
	else if (!ft_strncmp("WE", s, 2) && (s[2] == 0 || s[2] == ' '))
		return (1);
	else if (*s == 'C' && (s[1] == 0 || s[1] == ' '))
		return (1);
	else if (*s == 'F' && (s[1] == 0 || s[1] == ' '))
		return (1);
	return (0);
}

static void	get_config_sub(t_data *data, char *ptr, char *buf)
{
	if (!ft_strncmp("NO ", ptr, 3) && !data->config.north_texture)
		data->config.north_texture = get_text_path(data, buf);
	else if (!ft_strncmp("EA ", ptr, 3) && !data->config.east_texture)
		data->config.east_texture = get_text_path(data, buf);
	else if (!ft_strncmp("SO ", ptr, 3) && !data->config.south_texture)
		data->config.south_texture = get_text_path(data, buf);
	else if (!ft_strncmp("WE ", ptr, 3) && !data->config.west_texture)
		data->config.west_texture = get_text_path(data, buf);
	else if (!ft_strncmp("F ", ptr, 2) && !data->config.floor_color)
		data->config.floor_color = buf;
	else if (!ft_strncmp("C ", ptr, 2) && !data->config.ceiling_color)
		data->config.ceiling_color = buf;
	else
	{
		free(buf);
		if (is_config(ptr))
			error_exit("multipe definition for color or texture path ",
				data);
	}
}

int	check_map_newline(char **map)
{
	size_t	i;
	int		end;

	i = 0;
	end = 0;
	while (map[i])
	{
		if (end == 0)
		{
			if (ft_strlen(map[i]) == 0)
				end = 1;
		}
		else
		{
			if (ft_strlen(map[i]))
				return (0);
		}
		i++;
	}
	return (1);
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
		get_config_sub(data, ptr, buf);
		buf = NULL;
		i++;
	}
	if (!check_map_newline(data->config.raw_config + i))
		error_exit("invalid '\\n' inside of map", data);
}
