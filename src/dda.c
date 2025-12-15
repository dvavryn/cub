/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:53:02 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 16:15:13 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cast_ray_dda(t_data *cub, double angle, double *hitx, double *hity)
{
	t_dda	dda;
	int		mapx;
	int		mapy;

	dda.raydirx = cos(angle);
	dda.raydiry = sin(angle);
	mapy = (int)(cub->player.y / TILE);
	mapx = (int)(cub->player.x / TILE);
	if (dda.raydirx == 0)
		dda.deltadistx = 1e30;
	else
		dda.deltadistx = fabs(1 / dda.raydirx);
	if (dda.raydiry == 0)
		dda.deltadisty = 1e30;
	else
		dda.deltadisty = fabs(1 / dda.raydiry);
	dda.hit = 0;
	if (dda.raydirx < 0)
	{
		dda.stepx = -1;
		dda.sidedistx = (cub->player.x / TILE - mapx) * dda.deltadistx;
	}
	else
	{
		dda.stepx = 1;
		dda.sidedistx = (mapx + 1 - cub->player.x / TILE) * dda.deltadistx;
	}
	if (dda.raydiry < 0)
	{
		dda.stepy = -1;
		dda.sidedisty = (cub->player.y / TILE - mapy) * dda.deltadisty;
	}
	else
	{
		dda.stepy = 1;
		dda.sidedisty = (mapy + 1 - cub->player.y / TILE) * dda.deltadisty;
	}
	while (!dda.hit)
	{
		if (dda.sidedistx < dda.sidedisty)
		{
			dda.sidedistx += dda.deltadistx;
			mapx += dda.stepx;
			dda.side = 0;
		}
		else
		{
			dda.sidedisty += dda.deltadisty;
			mapy += dda.stepy;
			dda.side = 1;
		}
		if (mapy < 0 || mapx < 0 || !cub->map[mapy] || mapx >= (int)strlen(cub->map[mapy])) //ft_strlen
			break ;
		if (cub->map[mapy][mapx] == '1')
			dda.hit = 1;
	}
	if (dda.side == 0)
		dda.dist = dda.sidedistx - dda.deltadistx;
	else
		dda.dist = dda.sidedisty - dda.deltadisty;
	dda.dist = dda.dist * TILE;
	if (hitx)
		*hitx = cub->player.x + dda.raydirx * dda.dist;
	if (hity)
		*hity = cub->player.y + dda.raydiry * dda.dist;
	cub->dda = dda;
	return (dda.dist);
}
