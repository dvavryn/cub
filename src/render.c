/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:45:13 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 19:55:37 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_crosshair(t_data *cub)
{
	for (int y = WIN_H / 2 - 16; y < WIN_H / 2 + 15; y++)
	{
		if (y <= WIN_H / 2 - 2 || y > WIN_H / 2 + 2)
		{
			my_pixel_put(&cub->mlx.image, WIN_W / 2, y, 0x0);
			my_pixel_put(&cub->mlx.image, WIN_W / 2 + 1, y, 0x0);
		}
	}
	for (int x = WIN_W / 2 - 16; x < WIN_W / 2 + 15; x++)
	{
		if (x <= WIN_W / 2 - 2 || x > WIN_W / 2 + 2)
		{
			my_pixel_put(&cub->mlx.image, x, WIN_H / 2, 0x0);
			my_pixel_put(&cub->mlx.image, x, WIN_H / 2 + 1, 0x0);
		}
	}
}

void	render(t_data *cub)
{
	ft_bzero(cub->mlx.image.address, WIN_H * cub->mlx.image.line_length);
	cast_all_rays_3d(cub);
	draw_minimap(cub);
	draw_player(cub);
	cast_rays_minimap(cub);
	draw_crosshair(cub);
	mlx_put_image_to_window(cub->mlx.mlx, cub->mlx.win, cub->mlx.image.img, 0, 0);
}

int	render_loop(t_data *cub)
{
	render(cub);
	return (0);
}

int	get_wall_color(t_data *cub, double angle)
{
	if (cub->dda.side == 0)
	{
		if (cos(angle) > 0)
			return (0xED280E);
		else
			return (0x0E1EED);
	}
	else
	{
		if (sin(angle) > 0)
			return (0x27F538);
		else
			return (0xEBFF1F);
	}
}

t_img	*get_wall_texture(t_data *cub, t_dda *dda)
{
	if (dda->side == 0 && dda->raydirx > 0)
		return (&cub->mlx.east);
	if (dda->side == 0 && dda->raydirx < 0)
		return (&cub->mlx.west);
	if (dda->side == 1 && dda->raydiry > 0)
		return (&cub->mlx.south);
	return (&cub->mlx.north);
}

double	get_wall_x(t_data *cub, t_dda *dda, t_img *tex)
{
	double	wall_x;
	int		tex_x;

	if (dda->side == 0)
		wall_x = cub->player.y + dda->dist * dda->raydiry;
	else
		wall_x = cub->player.x + dda->dist * dda->raydirx;
	wall_x /= TILE;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
