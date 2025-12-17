/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:32:15 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/17 12:30:02 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	color_check_format(char *s)
{
	ssize_t	i;

	i = 0;
	while (s[++i] && ft_isdigit(s[i]))
		;
	if (s[i])
		return (0);
	return (1);
}

static int	convert_color(char *s, int *err)
{
	char	**split;
	size_t	i;
	int		j;
	int		out;

	split = ft_split(s + 2, ',');
	if (!split)
		return ((*err = 1), -1);
	i = 0;
	while (split[i])
	{
		j = 0;
		if (!color_check_format(split[i]))
			return (free_split(split), -1);
		j = ft_atoi(split[i]);
		if (j < 0 || j > 255)
			return (free_split(split), -1);
		i++;
	}
	if (i != 3)
		return (free_split(split), -1);
	out = (ft_atoi(split[0]) << 16) + (ft_atoi(split[1]) << 8)
		+ ft_atoi(split[2]);
	return (free_split(split), out);
}

void	check_colors(t_data *data)
{
	char	*c;
	char	*f;
	int		err;

	err = 0;
	c = data->config.ceiling_color;
	f = data->config.floor_color;
	data->config.floor_color_hex = convert_color(data->config.floor_color,
			&err);
	data->config.ceiling_color_hex = convert_color(data->config.ceiling_color,
			&err);
	if (err == 1)
		error_exit("malloc failed", data);
	else if (err == 2)
		error_exit("color format", data);
	if (data->config.floor_color_hex == -1
		|| data->config.ceiling_color_hex == -1)
		error_exit("wrong color format", data);
}
