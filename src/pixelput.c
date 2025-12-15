/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelput.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwarz <bschwarz@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:46:46 by bschwarz          #+#    #+#             */
/*   Updated: 2025/12/15 16:20:39 by bschwarz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	get_color(t_img *img, int x, int y)
{
	char	*dest;

	dest = img->address + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)dest);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->address + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
