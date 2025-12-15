/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 12:32:22 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 20:29:08 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	wasd(t_data *cub, double *new_x, double *new_y)
{
	if (cub->key[119])
	{
		*new_x += cub->player.dir_x * cub->player.move_speed;
		*new_y += cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->key[97])
	{
		*new_x += cub->player.dir_y * cub->player.move_speed;
		*new_y -= cub->player.dir_x * cub->player.move_speed;
	}
	if (cub->key[115])
	{
		*new_x -= cub->player.dir_x * cub->player.move_speed;
		*new_y -= cub->player.dir_y * cub->player.move_speed;
	}
	if (cub->key[100])
	{
		*new_y += cub->player.dir_x * cub->player.move_speed;
		*new_x -= cub->player.dir_y * cub->player.move_speed;
	}
}

void	key_handler(t_data *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player.x;
	new_y = cub->player.y;
	cub->player.move_speed = 150 * cub->delta;
	cub->player.rot_speed = 2.5 * cub->delta;
	wasd(cub, &new_x, &new_y);
	if (cub->key[65361])
		cub->player.angle -= cub->player.rot_speed;
	if (cub->key[65363])
		cub->player.angle += cub->player.rot_speed;
	cub->player.dir_x = cos(cub->player.angle);
	cub->player.dir_y = sin(cub->player.angle);
	if (!is_wall(cub->map.map, new_x, new_y))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

int	key_press(int key, t_data *cub)
{
	cub->key[key] = true;
	if (key == 65307)
		cross(cub);
	return (0);
}

int	key_release(int key, t_data *cub)
{
	cub->key[key] = false;
	return (0);
}
