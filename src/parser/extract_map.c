/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:32:51 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:43:03 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	extract_map(t_data *data)
{
	size_t	i;
	ssize_t	j;
	char	**out;

	out = ft_calloc(get_raw_map_size(data->config.raw_config) + 1,
			sizeof(char *));
	if (!out)
		error_exit("malloc failed", data);
	i = 0;
	while (data->config.raw_config[i] && (!data->config.raw_config[i][0]
		|| !ft_strchr(" \t01", data->config.raw_config[i][0])))
		i++;
	j = -1;
	while (data->config.raw_config[i])
	{
		out[++j] = ft_strdup(data->config.raw_config[i]);
		if (!out[j])
		{
			free_split(out);
			error_exit("malloc failed", data);
		}
		i++;
	}
	free_split(data->config.raw_config);
	data->config.raw_config = out;
}
