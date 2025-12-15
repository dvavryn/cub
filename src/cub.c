/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:46:21 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 17:37:03 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cub(void)
{
	t_data	cub;

	static char	*map[] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000001111100001010100001",
		"1000001000100000000000001",
		"1000001000100001000100001",
		"1000001000100000000000001",
		"1000001101100001010100001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1111111110000S00000000001",
		"1101000010000000000000001",
		"1100001010000000000000001",
		"1101000010000000000000001",
		"1101111110000000000000001",
		"1100000000000000000000001",
		"1111111110000000000000001",
		"1111111111111111111111111",
		NULL
	};
	bzero(cub.key, sizeof(cub.key)); //ft_bzero
	cub.map.map = map;
	cub.mlx.mlx = mlx_init();
	init_player_from_map(&cub);
	cub.mlx.win = mlx_new_window(cub.mlx.mlx, WIN_W, WIN_H, "cub3D");
	cub.mlx.image.img = mlx_new_image(cub.mlx.mlx, WIN_W, WIN_H);
	cub.mlx.image.address = mlx_get_data_addr(cub.mlx.image.img, &cub.mlx.image.bpp,
			&cub.mlx.image.line_length, &cub.mlx.image.endian);
	load_texture(&cub, &cub.mlx.north, cub.config.north_texture + 3);
	load_texture(&cub, &cub.mlx.east, cub.config.east_texture + 3);
	load_texture(&cub, &cub.mlx.south, cub.config.south_texture + 3);
	load_texture(&cub, &cub.mlx.west, cub.config.west_texture + 3);
	render(&cub);
	mlx_hook(cub.mlx.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.mlx.win, 3, 1L << 1, key_release, &cub);
	mlx_hook(cub.mlx.win, 17, 1L << 2, cross, &cub);
	mlx_loop_hook(cub.mlx.mlx, update, &cub);
	mlx_loop(cub.mlx.mlx);
}
