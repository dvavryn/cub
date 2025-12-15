/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:42:01 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 21:18:59 by bschwarz         ###   ########.fr       */
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

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	load_texture(t_data *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx.mlx,
			path, &tex->width, &tex->height);
	if (!tex->img)
		error_exit(path, cub);
	tex->address = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_length, &tex->endian);
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
	int		j;
	char	**out;

	h = 0;
	while (map[h])
		h++;
	out = malloc((h + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	out[h] = NULL;
	h = -1;
	while (map[++h])
	{
		out[h] = malloc(ft_strlen(map[h]) + 1);
		if (!out[h])
		{
			j = -1;
			while (++j < h)
				free(out[j]);
			return (free(out), NULL);
		}
		ft_strlcpy(out[h], map[h], ft_strlen(map[h]));
	}
	return (out);
}
