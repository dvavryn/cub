/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:12:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:23:00 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_data *data)
{
	if (data->mlx.mlx)
	{
		if (data->mlx.image.img)
			mlx_destroy_image(data->mlx.mlx, data->mlx.image.img);
		if (data->mlx.north.img)
			mlx_destroy_image(data->mlx.mlx, data->mlx.north.img);
		if (data->mlx.east.img)
			mlx_destroy_image(data->mlx.mlx, data->mlx.east.img);
		if (data->mlx.south.img)
			mlx_destroy_image(data->mlx.mlx, data->mlx.south.img);
		if (data->mlx.west.img)
			mlx_destroy_image(data->mlx.mlx, data->mlx.west.img);
		if (data->mlx.win)
			mlx_destroy_window(data->mlx.mlx, data->mlx.win);
		if (data->mlx.mlx)
		{
			mlx_destroy_display(data->mlx.mlx);
			free(data->mlx.mlx);
		}
	}
}

void	free_data(t_data *data)
{
	size_t	i;

	if (data->config.raw_config)
		free_split(data->config.raw_config);
	if (data->config.north_texture)
		free(data->config.north_texture);
	if (data->config.east_texture)
		free(data->config.east_texture);
	if (data->config.south_texture)
		free(data->config.south_texture);
	if (data->config.west_texture)
		free(data->config.west_texture);
	if (data->config.ceiling_color)
		free(data->config.ceiling_color);
	if (data->config.floor_color)
		free(data->config.floor_color);
	if (data->map.map)
	{
		i = -1;
		while (data->map.map[++i])
			free(data->map.map[i]);
		free(data->map.map);
	}
	free_mlx(data);
}
