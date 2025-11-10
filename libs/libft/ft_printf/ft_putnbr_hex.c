/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:52:38 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 15:31:37 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	getlen_hex(unsigned int n);

int	ft_putnbr_hex(int c, unsigned int n)
{
	unsigned int	i;
	char			*radix;
	size_t			l;

	l = getlen_hex(n);
	if (c == 'x')
		radix = "0123456789abcdef";
	if (c == 'X')
		radix = "0123456789ABCDEF";
	i = 0;
	if (n >= 16)
		ft_putnbr_hex(c, n / 16);
	while (i < n % 16)
		i++;
	write(1, &radix[i], 1);
	return (l);
}

static int	getlen_hex(unsigned int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
