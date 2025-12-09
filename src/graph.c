/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:32:07 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/09 16:54:57 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(unsigned int*)dest = color;
}

int	pixel_get(t_img *img, int x, int y)
{
	char	*dest;

	dest = img->addr + (y * img->ll + x * (img->bpp / 8));
	return (*(unsigned int*)dest);
}

void	load_textures(t_data *data)
{
	data->mlx.north.img = mlx_xpm_file_to_image(data->mlx.mlx, data->config.north_texture + 3, &data->mlx.north.x, &data->mlx.north.y);
	data->mlx.east.img = mlx_xpm_file_to_image(data->mlx.mlx, data->config.east_texture + 3, &data->mlx.east.x, &data->mlx.east.y);
	data->mlx.south.img = mlx_xpm_file_to_image(data->mlx.mlx, data->config.south_texture + 3, &data->mlx.south.x, &data->mlx.south.y);
	data->mlx.west.img = mlx_xpm_file_to_image(data->mlx.mlx, data->config.west_texture + 3, &data->mlx.west.x, &data->mlx.west.y);
	if (!data->mlx.north.img || !data->mlx.east.img || !data->mlx.south.img || !data->mlx.west.img)
		error_exit("textures failed loading", data);
	data->mlx.north.addr = mlx_get_data_addr(data->mlx.north.img, &data->mlx.north.bpp, &data->mlx.north.ll, &data->mlx.north.endian);
	data->mlx.east.addr = mlx_get_data_addr(data->mlx.east.img, &data->mlx.east.bpp, &data->mlx.east.ll, &data->mlx.east.endian);
	data->mlx.south.addr = mlx_get_data_addr(data->mlx.south.img, &data->mlx.south.bpp, &data->mlx.south.ll, &data->mlx.south.endian);
	data->mlx.west.addr = mlx_get_data_addr(data->mlx.west.img, &data->mlx.west.bpp, &data->mlx.west.ll, &data->mlx.west.endian);
}

void	init_graph(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		error_exit("mlx_init failed", data);
	data->mlx.win = mlx_new_window(data->mlx.mlx, WIDHT, HEIGHT, "cub3D");
	if (!data->mlx.win)
		error_exit("mlx_new_window failed", data);
	data->mlx.img.img = mlx_new_image(data->mlx.mlx, WIDHT, HEIGHT);
	if (!data->mlx.img.img)
		error_exit("mlx_new_image failed", data);
	data->mlx.img.addr = mlx_get_data_addr(data->mlx.img.img,
		&data->mlx.img.bpp, &data->mlx.img.ll, &data->mlx.img.endian);
	load_textures(data);
}

int	destroy(void *data)
{
	(void)data;
	printf("i am not freed yet!\n");
	exit(0);
	return 0;
}