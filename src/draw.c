/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:21:15 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 21:37:05 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_line(t_img *img, t_point start, t_point end)
{
	int		i;
	double	dx;
	double	dy;
	double	steps;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps == 0)
	{
		my_pixel_put(img, (int)round(start.x), (int)round(start.y), 0x00FF00);
		return ;
	}
	dx /= steps;
	dy /= steps;
	i = -1;
	while (++i < (int)steps)
	{
		my_pixel_put(img, (int)round(start.x), (int)round(start.y), 0x00FF00);
		start.x += dx;
		start.y += dy;
	}
}

void	draw_minimap_ray(t_data *cub, double end_x, double end_y)
{
	int		map_width;
	int		map_height;
	double	tile_size;
	double	ray_tile_x;
	double	ray_tile_y;

	map_width = (int)cub->map.map_x;
	map_height = (int)cub->map.map_y;
	tile_size = fmin((double)MINI_SIZE / (double)map_width,
			(double)MINI_SIZE / (double)map_height);
	ray_tile_x = end_x / TILE;
	ray_tile_y = end_y / TILE;
	if (ray_tile_x < 0)
		ray_tile_x = 0;
	if (ray_tile_x >= map_width)
		ray_tile_x = map_width - 1;
	if (ray_tile_y < 0)
		ray_tile_y = 0;
	if (ray_tile_y >= map_height)
		ray_tile_y = map_height - 1;
	draw_line(&cub->mlx.image, (t_point){.x = MINI_OFFSET + (cub->player.x
			/ TILE) * tile_size, .y = MINI_OFFSET + (cub->player.y / TILE)},
		(t_point){.x = MINI_OFFSET + ray_tile_x * tile_size,
		.y = MINI_OFFSET + ray_tile_y * tile_size});
}

int	ray_color(double dist)
{
	int	intensity;

	intensity = 255 - (int)(dist * 0.15);
	if (intensity < 20)
		intensity = 20;
	return (intensity << 8);
}
