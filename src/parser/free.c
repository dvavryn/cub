/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:12:55 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 19:07:15 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	// not finished yet... mlx stuff
}
