/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:13:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:45:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// strerror: error message, data: either data or NULL
void	error_exit(char *str, t_data *data)
{
	ft_putstr_fd("cub3d: Error: ", STDERR_FILENO);
	if (errno)
	{
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	else
		ft_putendl_fd(str, STDERR_FILENO);
	if (data)
		free_data(data);
	exit(1);
}

int	cross(t_data *data)
{
	if (data)
		free_data(data);
	exit(1);
	return (0);
}

size_t	get_raw_map_size(char **config)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (config[i] && !ft_strchr(" \t 01", config[i][0]))
		i++;
	while (config[j])
		j++;
	return (j - i);
}

size_t	get_size_map(char **config, char c)
{
	size_t	out;
	size_t	i;

	out = 0;
	if (c == 'l')
	{
		i = 0;
		while (config[i])
		{
			if (ft_strlen(config[i]) > out)
				out = ft_strlen(config[i]);
			i++;
		}
	}
	else
	{
		while (config[out])
			out++;
	}
	return (out);
}
