/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:36:01 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:43:33 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	try_open(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

void	validate_files(t_data *data)
{
	if (!try_open(data->config.north_texture))
		error_exit("north_texture invalid", data);
	if (!try_open(data->config.east_texture))
		error_exit("east_texture invalid", data);
	if (!try_open(data->config.south_texture))
		error_exit("south_texture invalid", data);
	if (!try_open(data->config.west_texture))
		error_exit("west_texture invalid", data);
}
