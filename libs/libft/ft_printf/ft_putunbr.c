/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:37:49 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 15:31:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	getlen_un(unsigned int n);

int	ft_putunbr(unsigned int n)
{
	size_t	l;

	l = getlen_un(n);
	if (n >= 10)
	{
		ft_putunbr(n / 10);
	}
	ft_putchar((n % 10) + '0');
	return (l);
}

static int	getlen_un(unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
