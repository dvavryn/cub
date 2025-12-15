/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:21:15 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 16:36:49 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	get_map_dimensions(cub->map, &map_width, &map_height);
	my = 0;
	tile_size = 128 / (double)map_width;
	if (128 / (double)map_height < tile_size)
		tile_size = 128 / (double)map_height;
	while (my < map_height)
	{
		mx = 0;
		while (mx < map_width)
		{
			color = 0x999999;
			if (mx < (int)strlen(cub->map[my]) && cub->map[my][mx] == '1') //ft_strlen
				color = 0x444444;
			draw_square(&cub->image, MINI_OFFSET + (int)(mx * tile_size),
				MINI_OFFSET + (int)(my * tile_size), tile_size + 0.9999, color);
			mx++;
		}
		my++;
	}
}

void	draw_player(t_data *cub)
{
	int		minix;
	int		miniy;
	int		map_width;
	int		map_height;
	double	tile_size;

	get_map_dimensions(cub->map, &map_width, &map_height);
	if (128 / map_width < 128 / map_height)
		tile_size = 128 / map_width;
	else
		tile_size = 128 / map_height;
	minix = MINI_OFFSET + (int)(cub->player.x / TILE * tile_size);
	miniy = MINI_OFFSET + (int)(cub->player.y / TILE * tile_size);
	draw_circle(&cub->image, minix, miniy, 2, 0xFF0000);
}

void	draw_line(t_img *img, double x0, double y0, double x1, double y1)
{
	int		i;
	double	dx;
	double	dy;
	double	steps;

	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	else
		steps = fabs(dy);
	if (steps == 0)
	{
		my_pixel_put(img, (int)round(x0), (int)round(y0), 0x00FF00);
		return ;
	}
	dx /= steps;
	dy /= steps;
	i = -1;
	while (++i < (int)steps)
	{
		my_pixel_put(img, (int)round(x0), (int)round(y0), 0x00FF00);
		x0 += dx;
		y0 += dy;
	}
}

void	draw_minimap_ray(t_data *cub, double end_x, double end_y)
{
	int		map_width;
	int		map_height;
	double	tile_size;
	double	ray_tile_x;
	double	ray_tile_y;

	get_map_dimensions(cub->map, &map_width, &map_height);
	if (128 / map_width < 128 / map_height)
		tile_size = 128 / map_width;
	else
		tile_size = 128 / map_height;
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
	draw_line(&cub->image, MINI_OFFSET + (cub->player.x / TILE) * tile_size, MINI_OFFSET + (cub->player.y / TILE) * tile_size,
		MINI_OFFSET + ray_tile_x * tile_size, MINI_OFFSET + ray_tile_y * tile_size);
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
		my_pixel_put(&cub->image, x, y, 0x87CEEB);
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
		my_pixel_put(&cub->image, x, y, color);
		tex_pos += tex_step;
		y++;
	}
	y = bottom + 1;
	while (y < WIN_H)
	{
		my_pixel_put(&cub->image, x, y, 0x451800);
		y++;
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
