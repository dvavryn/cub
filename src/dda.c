/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:53:02 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/17 14:19:33 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_ray_dda_sub_one(t_data *cub, t_dda *dda)
{
	if (dda->raydirx < 0)
	{
		dda->stepx = -1;
		dda->sidedistx = (cub->player.x / TILE - dda->mapx) * dda->deltadistx;
	}
	else
	{
		dda->stepx = 1;
		dda->sidedistx = (dda->mapx + 1 - cub->player.x / TILE)
			* dda->deltadistx;
	}
	if (dda->raydiry < 0)
	{
		dda->stepy = -1;
		dda->sidedisty = (cub->player.y / TILE - dda->mapy) * dda->deltadisty;
	}
	else
	{
		dda->stepy = 1;
		dda->sidedisty = (dda->mapy + 1 - cub->player.y / TILE)
			* dda->deltadisty;
	}
}

static void	cast_ray_dda_sub_two(t_data *cub, t_dda *dda)
{
	while (!dda->hit)
	{
		if (dda->sidedistx < dda->sidedisty)
		{
			dda->sidedistx += dda->deltadistx;
			dda->mapx += dda->stepx;
			dda->side = 0;
		}
		else
		{
			dda->sidedisty += dda->deltadisty;
			dda->mapy += dda->stepy;
			dda->side = 1;
		}
		if (dda->mapy < 0 || dda->mapx < 0 || dda->mapy >= (int)cub->map.map_y
			|| dda->mapx >= (int)cub->map.map_x)
			break ;
		if (cub->map.map[dda->mapy][dda->mapx] == 1)
			dda->hit = 1;
	}
	if (dda->side == 0)
		dda->dist = dda->sidedistx - dda->deltadistx;
	else
		dda->dist = dda->sidedisty - dda->deltadisty;
	dda->dist = dda->dist * TILE;
}

double	cast_ray_dda(t_data *cub, double angle, double *hitx, double *hity)
{
	t_dda	*dda;

	dda = &cub->dda;
	dda->raydirx = cos(angle);
	dda->raydiry = sin(angle);
	dda->mapy = (int)(cub->player.y / TILE);
	dda->mapx = (int)(cub->player.x / TILE);
	if (dda->raydirx == 0)
		dda->deltadistx = 1e30;
	else
		dda->deltadistx = fabs(1 / dda->raydirx);
	if (dda->raydiry == 0)
		dda->deltadisty = 1e30;
	else
		dda->deltadisty = fabs(1 / dda->raydiry);
	dda->hit = 0;
	cast_ray_dda_sub_one(cub, dda);
	cast_ray_dda_sub_two(cub, dda);
	if (hitx)
		*hitx = cub->player.x + dda->raydirx * dda->dist;
	if (hity)
		*hity = cub->player.y + dda->raydiry * dda->dist;
	return (dda->dist);
}
