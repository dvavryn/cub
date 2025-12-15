/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:33:35 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:43:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map(t_data*data, int **map, size_t x, size_t y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			if (!map[i][j])
			{
				if (i == 0 || j == 0 || j + 1 == x || i + 1 == y)
					error_exit("map not surrounded by walls", data);
				else if ((i - 1 >= 0 && map[i - 1][j] == -1)
					|| (i + 1 < y && map[i + 1][j] == -1)
					|| (j - 1 >= 0 && map[i][j - 1] == -1)
					|| (j + 1 < x && map[i][j + 1] == -1))
					error_exit("map not surrounded by walls", data);
			}
			j++;
		}
		i++;
	}
}

static void	convert_map(t_data *data, char **con)
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

static void	alloc_map(t_data *data, char **config)
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
	if (!data->config.player_orientation)
		error_exit("no player on the map!", data);
}

void	validate_map(t_data *data)
{
	check_chars(data, data->config.raw_config);
	alloc_map(data, data->config.raw_config);
	convert_map(data, data->config.raw_config);
	check_map(data, data->map.map, data->map.map_x, data->map.map_y);
}
