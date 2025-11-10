/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 22:26:34 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 15:31:24 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	getlen_p(void *p);

int	ft_padress(void *p)
{
	unsigned long	adr;

	if (!p)
	{
		ft_puts("(nil)");
		return (5);
	}
	write(1, "0x", 2);
	adr = (unsigned long)p;
	ft_putulong_hex(adr);
	return (getlen_p(p));
}

static int	getlen_p(void *p)
{
	unsigned long	l;
	size_t			i;

	i = 0;
	l = (unsigned long)p;
	while (l > 0)
	{
		l /= 16;
		i++;
	}
	i += 2;
	return (i);
}
