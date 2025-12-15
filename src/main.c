/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:10:05 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 17:37:17 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	print_data(t_data *data)		// delete
{
	t_config *c = &data->config;
	t_map *m = &data->map;
	printf(
	"Config\n"
	"\tNorth: %s\n\tEast:  %s\n\tSouth: %s\n\tWest:  %s\n\n"
	"\tFloor:   %s - 0x%x\n\tCeiling: %s - 0x%x\n\n\tPos-X:		  %d\n\t"
	"Pos-Y:		  %d\n\tOrientations: %c\n\n\nMap\n\tsize x: %zu\n"
	"\tsize y: %zu\n"
	, c->north_texture, c->east_texture, c->south_texture, c->west_texture,
	c->floor_color, c->floor_color_hex, c->ceiling_color, c->ceiling_color_hex,
	c->player_position_x, c->player_position_y, 
		c->player_orientation, m->map_x, m->map_y);
	for(int i = 0; m->map[i]; i++)
	{
		printf("\t");
		for (int j = 0; (size_t)j < m->map_x; j++)
		{
			if (m->map[i][j] < 0)
				printf("[%d ]", m->map[i][j]);
			else
				printf("[ %d ]", m->map[i][j]);

		}
		printf("\n");
	}	
}

int	main(int argc, char **argv)
{
	t_data	data;

	parsing(&data, argc, argv);
	free_data(&data);
	return (0);
}
