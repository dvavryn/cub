/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:09:34 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/09 15:04:29 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# define WIDHT 1280
# define HEIGHT 720

#include "libft.h"
#include <X11/keysym.h>
#include <mlx.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

typedef struct s_data t_data;
typedef struct s_config t_config;
typedef struct s_map t_map;
typedef struct s_img t_img;
typedef struct s_mlx t_mlx;

struct s_config
{
	char	**raw_config;

	char	*north_texture;	//
	char	*east_texture;	//
	char	*south_texture;	//
	char	*west_texture;	//
	char	*floor_color;
	int		floor_color_hex;//
	char	*ceiling_color;
	int		ceiling_color_hex;//
	int		player_position_x;//
	int		player_position_y;//
	char	player_orientation;//
};

struct s_map
{
	int		**map;//
	size_t	map_x;//
	size_t	map_y;//
};

struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		x;
	int		y;
};

struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;

	t_img	north;
	t_img	east;
	t_img	south;
	t_img	west;
};

struct s_data
{
	t_config	config;//
	t_map		map;//
	t_mlx		mlx;
};

void	free_data(t_data *data);
void	error_exit(char *str, t_data *data);
void	parsing(t_data *data, int argc, char **argv);


void	init_graph(t_data *data);
int	destroy(void *data);

#endif