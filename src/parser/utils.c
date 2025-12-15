/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:13:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 20:13:12 by dvavryn          ###   ########.fr       */
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
