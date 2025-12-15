/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:35:54 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 21:41:34 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void part_two(t_data *cub, int x, t_draw *d)
{
	while (d->y <= d->bottom)
	{
		d->tex_y = (int)d->tex_pos;
		if (d->tex_y < 0)
			d->tex_y = 0;
		if (d->tex_y >= d->tex->height)
			d->tex_y = d->tex->height - 1;
		d->color = d->tex_pix[d->tex_y * d->tex->width + d->tex_x];
		my_pixel_put(&cub->mlx.image, x, d->y, d->color);
		d->tex_pos += d->tex_step;
		d->y++;
	}
	d->y = d->bottom + 1;
	while (d->y < WIN_H)
	{
		my_pixel_put(&cub->mlx.image, x, d->y, 0x451800);
		d->y++;
	}
}


void	draw_3d_wall(t_data *cub, int x, double dist)
{
	t_draw d;

	d.tex = get_wall_texture(cub, &cub->dda);
	{
		d.proj_plane = (WIN_W / 2.0) / tan(FOV / 2.0);
		d.wall_h = (TILE / dist) * d.proj_plane;
	}
	d.top = (WIN_H / 2) - (d.wall_h / 2);
	d.bottom = (WIN_H / 2) + (d.wall_h / 2);
	if (d.top < 0)
		d.top = 0;
	if (d.bottom >= WIN_H)
		d.bottom = WIN_H - 1;
	d.y = -1;
	while (++d.y < d.top)
		my_pixel_put(&cub->mlx.image, x, d.y, 0x87CEEB);
	d.tex_x = get_wall_x(cub, &cub->dda, d.tex);
	d.tex_step = (double)d.tex->height / d.wall_h;
	d.tex_pos = (d.top - WIN_H / 2 + d.wall_h / 2) * d.tex_step;
	d.tex_pix = (int *)d.tex->address;
	d.y = d.top;
	part_two(cub, x, &d);
}
