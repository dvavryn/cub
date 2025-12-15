/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:45:13 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 15:51:55 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render(t_data *cub)
{
	bzero(cub->image.address, WIN_H * cub->image.line_length); //ft_bzero
	cast_all_rays_3d(cub);
	draw_minimap(cub);
	draw_player(cub);
	cast_rays_minimap(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->image.img, 0, 0);
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
		return (&cub->east);
	if (dda->side == 0 && dda->raydirx < 0)
		return (&cub->west);
	if (dda->side == 1 && dda->raydiry > 0)
		return (&cub->south);
	return (&cub->north);
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
