/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:25:46 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/23 14:07:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	argcheck(int argc, char **argv)
{
	size_t	len;

	if (argc < 2)
		error_exit("filename missing", NULL);
	else if (argc > 2)
		error_exit("Usage: ./cub3d file.cub", NULL);
	len = ft_strlen(argv[1]);
	if (!len)
		error_exit("empty filename", NULL);
	else if ((len <= 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		|| (ft_strchr(argv[1], '/')
			&& !ft_strncmp(ft_strrchr(argv[1], '/') + 1, ".cub", 4)))
		error_exit("invalid file extension. expected '.cub'", NULL);
}

static void	check_garbage(t_data *data)
{
	ssize_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	while (data->config.raw_config[++i])
	{
		j = 0;
		ptr = data->config.raw_config[i];
		while (ptr[j] && ft_isspace(ptr[j]))
			j++;
		if (ft_strlen(ptr) == 0 || ((!ft_strncmp("NO", &ptr[j], 2)
					|| !ft_strncmp("SO", &ptr[j], 2)
					|| !ft_strncmp("EA", &ptr[j], 2)
					|| !ft_strncmp("WE", &ptr[j], 2)) && ft_isspace(ptr[j + 2]))
			|| ((ptr[j] == 'C' || ptr[j] == 'F') && ft_isspace(ptr[j + 1]))
			|| ptr[j] == '1')
			continue ;
		else
			error_exit("invalid line in config", data);
	}
}

void	parsing(t_data *data, int argc, char **argv)
{
	ft_bzero(data, sizeof(t_data));
	argcheck(argc, argv);
	read_config(data, argv[1]);
	check_garbage(data);
	get_config(data, 0);
	if (!data->config.north_texture || !data->config.east_texture
		|| !data->config.south_texture || !data->config.west_texture)
		error_exit("textures missing", data);
	if (!data->config.floor_color || !data->config.ceiling_color)
		error_exit("colors missing", data);
	check_colors(data);
	extract_map(data);
	validate_map(data);
	validate_files(data);
}
