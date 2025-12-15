/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:03:29 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 21:04:53 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cune3d.h"

void	draw_square(t_img *img, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			my_pixel_put(img, x + j, y + i, color);
	}
}

void	draw_minimap(t_data *cub)
{
	int		mx;
	int		my;
	int		map_width;
	int		map_height;
	int		color;
	double	tile_size;
	int		size_i;

	map_height = (int)cub->map.map_y;
	map_width = (int)cub->map.map_x;
	my = 0;
	tile_size = fmin((double)MINI_SIZE / (double)map_width,
			(double)MINI_SIZE / (double)map_height);
	size_i = (int)ceil(tile_size);
	while (my < map_height)
	{
		mx = 0;
		while (mx < map_width)
		{
			if (cub->map.map[my][mx] != -1)
			{
				color = 0x999999;
				if (cub->map.map[my][mx] == 1)
					color = 0x444444;
				draw_square(&cub->mlx.image, MINI_OFFSET + (int)(mx * tile_size),
					MINI_OFFSET + (int)(my * tile_size), size_i, color);
			}
			mx++;
		}
		my++;
	}
}

void	draw_circle(t_img *img, int x, int y, int r, int color)
{
	int	dx;
	int	dy;

	dy = -r;
	while (dy <= r)
	{
		dx = -r;
		while (dx <= r)
		{
			if (dx * dx + dy * dy <= r * r)
				my_pixel_put(img, x + dx, y + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_player(t_data *cub)
{
	int		minix;
	int		miniy;
	int		map_width;
	int		map_height;
	double	tile_size;

	map_width = (int)cub->map.map_x;
	map_height = (int)cub->map.map_y;
	tile_size = fmin((double)MINI_SIZE / (double)map_width,
			(double)MINI_SIZE / (double)map_height);
	minix = MINI_OFFSET + (int)((cub->player.x / TILE) * tile_size);
	miniy = MINI_OFFSET + (int)((cub->player.y / TILE) * tile_size);
	draw_circle(&cub->mlx.image, minix, miniy, 2, 0xFF0000);
}
