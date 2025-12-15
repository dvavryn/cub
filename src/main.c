/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:46:21 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 16:20:18 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
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
	cub.map = map;
	cub.mlx = mlx_init();
	init_player_from_map(&cub);
	cub.win = mlx_new_window(cub.mlx, WIN_W, WIN_H, "cub3D");
	cub.image.img = mlx_new_image(cub.mlx, WIN_W, WIN_H);
	cub.image.address = mlx_get_data_addr(cub.image.img, &cub.image.bpp,
			&cub.image.line_length, &cub.image.endian);
	load_texture(&cub, &cub.north, "textures/north.xpm");
	load_texture(&cub, &cub.east, "textures/east.xpm");
	load_texture(&cub, &cub.south, "textures/south.xpm");
	load_texture(&cub, &cub.west, "textures/west.xpm");
	render(&cub);
	mlx_hook(cub.win, 2, 1L << 0, key_press, &cub);
	mlx_hook(cub.win, 3, 1L << 1, key_release, &cub);
	mlx_loop_hook(cub.mlx, update, &cub);
	mlx_loop(cub.mlx);
}
