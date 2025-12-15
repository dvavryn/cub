/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:21:15 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 21:28:11 by dvavryn          ###   ########.fr       */
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

void	draw_3d_wall(t_data *cub, int x, double dist)
{
	t_img	*tex;
	int		top;
	int		bottom;
	double	wall_h;
	double	tex_step;
	double	tex_pos;
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	int		*tex_pix;
	double	proj_plane;

	tex = get_wall_texture(cub, &cub->dda);
	{
		proj_plane = (WIN_W / 2.0) / tan(FOV / 2.0);
		wall_h = (TILE / dist) * proj_plane;
	}
	top = (WIN_H / 2) - (wall_h / 2);
	bottom = (WIN_H / 2) + (wall_h / 2);
	if (top < 0)
		top = 0;
	if (bottom >= WIN_H)
		bottom = WIN_H - 1;
	y = -1;
	while (++y < top)
		my_pixel_put(&cub->mlx.image, x, y, 0x87CEEB);
	tex_x = get_wall_x(cub, &cub->dda, tex);
	tex_step = (double)tex->height / wall_h;
	tex_pos = (top - WIN_H / 2 + wall_h / 2) * tex_step;
	tex_pix = (int *)tex->address;
	y = top;
	while (y <= bottom)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		color = tex_pix[tex_y * tex->width + tex_x];
		my_pixel_put(&cub->mlx.image, x, y, color);
		tex_pos += tex_step;
		y++;
	}
	y = bottom + 1;
	while (y < WIN_H)
	{
		my_pixel_put(&cub->mlx.image, x, y, 0x451800);
		y++;
	}
}

int	ray_color(double dist)
{
	int	intensity;

	intensity = 255 - (int)(dist * 0.15);
	if (intensity < 20)
		intensity = 20;
	return (intensity << 8);
}
