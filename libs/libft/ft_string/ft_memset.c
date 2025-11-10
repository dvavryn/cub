/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 12:26:33 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 01:06:48 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	uc;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	uc = (unsigned char)c;
	while (n > 0)
	{
		ptr[i] = uc;
		i++;
		n--;
	}
	return (s);
}
