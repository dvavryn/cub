/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:25:46 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:39:07 by dvavryn          ###   ########.fr       */
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
	else if (len <= 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		error_exit("invalid file extension. expected '.cub'", NULL);
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
	check_colors(data);
	extract_map(data);
	validate_map(data);
	validate_files(data);
}
