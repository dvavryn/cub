/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:46:21 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 20:42:29 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub(t_data *cub)
{
	ft_bzero(cub->key, sizeof(cub->key));
	cub->mlx.mlx = mlx_init();
	if (!cub->mlx.mlx)
		error_exit("mlx failed", cub);
	init_player_from_map(cub);
	cub->mlx.win = mlx_new_window(cub->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->mlx.mlx)
		error_exit("mlx failed", cub);
	cub->mlx.image.img = mlx_new_image(cub->mlx.mlx, WIN_W, WIN_H);
	cub->mlx.image.address = mlx_get_data_addr(cub->mlx.image.img,
			&cub->mlx.image.bpp, &cub->mlx.image.line_length,
			&cub->mlx.image.endian);
	load_texture(cub, &cub->mlx.north, cub->config.north_texture);
	load_texture(cub, &cub->mlx.east, cub->config.east_texture);
	load_texture(cub, &cub->mlx.south, cub->config.south_texture);
	load_texture(cub, &cub->mlx.west, cub->config.west_texture);
	render(cub);
	mlx_hook(cub->mlx.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->mlx.win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->mlx.win, 17, 1L << 2, cross, cub);
	mlx_loop_hook(cub->mlx.mlx, update, cub);
	mlx_loop(cub->mlx.mlx);
}
