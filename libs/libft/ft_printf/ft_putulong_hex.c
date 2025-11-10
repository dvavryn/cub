/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulong_hex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:48:34 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 15:31:45 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	getlen_ulhex(unsigned long n);

int	ft_putulong_hex(unsigned long n)
{
	unsigned long	i;
	char			*radix;
	size_t			l;

	l = getlen_ulhex(n);
	radix = "0123456789abcdef";
	i = 0;
	if (n >= 16)
		ft_putulong_hex(n / 16);
	while (i < n % 16)
		i++;
	write(1, &radix[i], 1);
	return (l);
}

static int	getlen_ulhex(unsigned long n)
{
	size_t	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
