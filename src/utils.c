/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:13:42 by dvavryn           #+#    #+#             */
/*   Updated: 2025/11/10 19:13:51 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// strerror: error message, data: either data or NULL
void	error_exit(char *strerror, t_data *data)
{
	if (data)
		free_data(data);
	if (strerror)
	{
		ft_putstr_fd("cub3d: Error: ", STDERR_FILENO);
		ft_putendl_fd(strerror, STDERR_FILENO);
	}
	else
		ft_putendl_fd("cub3d: miscellaneous error!", STDERR_FILENO);
	exit(1);
}