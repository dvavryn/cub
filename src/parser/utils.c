/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:13:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/12/15 19:57:33 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// strerror: error message, data: either data or NULL
void	error_exit(char *str, t_data *data)
{
	if (data)
		free_data(data);
	ft_putstr_fd("cub3d: Error: ", STDERR_FILENO);
	if (errno)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	else
		ft_putendl_fd(str, STDERR_FILENO);
	exit(1);
}

int	cross(t_data *data)
{
	if (data)
		free_data(data);
	exit(1);
	return (0);
}
