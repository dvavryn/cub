/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:09:34 by dvavryn           #+#    #+#             */
/*   Updated: 2025/11/10 19:30:18 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

#include "libft.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef struct s_data t_data;
typedef struct s_config t_config;
typedef struct s_map t_map;

struct s_config
{
	char	**raw_input;

	char	*north_texture;
	char	*east_texture;
	char	*south_texture;
	char	*west_texture;
	int		floor_color;
	int		ceiling_color;
	int		player_position_x;
	int		player_position_y;
	char	player_orientation;	
};

struct s_map
{
	int		**map;
	size_t	map_x;
	size_t	map_y;
};

struct s_data
{
	t_config	config;
	t_map		map;
};

void	free_data(t_data *data);
void	error_exit(char *strerr, t_data *data);
void	parsing(t_data *data, int argc, char **argv);
#endif