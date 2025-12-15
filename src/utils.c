/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:42:01 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 19:40:50 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(int **map, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE);
	map_y = (int)(y / TILE);
	if (map[map_y][map_x] == 1)
		return (1);
	return (0);
}

int	ray_color(double dist)
{
	int	intensity;

	intensity = 255 - (int)(dist * 0.15);
	if (intensity < 20)
		intensity = 20;
	return (intensity << 8);
}

static double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	update(t_data *cub)
{
	double	now;

	now = get_time();
	cub->delta = (now - cub->last_frame_time) / 1000;
	cub->last_frame_time = now;
	key_handler(cub);
	render(cub);
	return (0);
}

void	load_texture(t_data *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx.mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		exit(1); //exit function
	tex->address = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_length, &tex->endian);
}

void	init_player_from_map(t_data *cub)
{
	cub->player.x = (cub->config.player_position_x + 0.5) * TILE;
	cub->player.y = (cub->config.player_position_y + 0.5) * TILE;
	if (cub->config.player_orientation == 'N')
		cub->player.angle = -M_PI / 2;
	else if (cub->config.player_orientation == 'O')
		cub->player.angle = 0;
	else if (cub->config.player_orientation == 'S')
		cub->player.angle = M_PI / 2;
	else
		cub->player.angle = M_PI;
	cub->player.dir_x = cos(cub->player.angle);
	cub->player.dir_y = sin(cub->player.angle);
}

char	**duplicate_map(char **map)
{
	int		h;
	int		i;
	int		j;
	char	**out;

	h = 0;
	while (map[h])
		h++;
	out = malloc((h + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[h] = NULL;
	i = -1;
	while (++i < h)
	{
		out[i] = malloc(strlen(map[i]) + 1); //ft_strlen
		if (!out[i])
		{
			j = -1;
			while (++j < i)
				free(out[j]);
			free(out);
			return (NULL);
		}
		strcpy(out[i], map[i]); //ft_strcpy
	}
	return (out);
}
