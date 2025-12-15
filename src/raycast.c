/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:35:37 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 16:23:42 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	cast_ray(t_data *cub, double angle, double *hit_x, double *hit_y)
{
	double	x;
	double	y;
	double	ray_x;
	double	ray_y;
	double	dist;

	x = cub->player.x;
	y = cub->player.y;
	ray_x = cos(angle);
	ray_y = sin (angle);
	dist = 0;
	while (dist < MAX_DIST)
	{
		x += ray_x * RAY_STEP;
		y += ray_y * RAY_STEP;
		dist += RAY_STEP;
		if (x < 0 || x >= (double)WIN_W || y < 0 || y >= (double)WIN_H
			|| is_wall(cub->map, x, y))
			break ;
	}
	if (hit_x)
		*hit_x = x;
	if (hit_y)
		*hit_y = y;
	return (dist);
}

void	cast_all_rays(t_data *cub)
{
	int		i;
	double	start;
	double	angle;
	double	hitx;
	double	hity;

	start = cub->player.angle - (FOV / 2);
	i = 0;
	while (i < 60)
	{
		angle = start + i * (FOV) / 60;
		cast_ray_dda(cub, angle, &hitx, &hity);
		draw_minimap_ray(cub, hitx, hity);
		i++;
	}
}

void	cast_rays_minimap(t_data *cub)
{
	int		i;
	double	angle;
	double	start_angle;
	double	hitx;
	double	hity;

	start_angle = cub->player.angle - (FOV / 2);
	i = 0;
	while (i < 60)
	{
		angle = start_angle + i * (FOV / 60);
		cast_ray_dda(cub, angle, &hitx, &hity);
		cast_all_rays(cub);
		i++;
	}
}

void	cast_all_rays_3d(t_data *cub)
{
	double	angle;
	double	step;
	double	start;
	int		i;

	step = FOV / NUM_RAYS;
	start = cub->player.angle - FOV / 2;
	i = -1;
	while (++i < NUM_RAYS)
	{
		angle = start + i * step;
		cast_3d_ray(cub, angle, i);
	}
}

void	cast_3d_ray(t_data *cub, double angle, int col)
{
	double	hitx;
	double	hity;
	double	dist;
	double	corrected;

	dist = cast_ray_dda(cub, angle, &hitx, &hity);
	corrected = dist * cos(angle - cub->player.angle);
	draw_3d_wall(cub, col, corrected);
}
