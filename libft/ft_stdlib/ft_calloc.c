/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:53:02 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 01:06:06 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*out;
	size_t			total;
	size_t			i;
	unsigned char	*ptr;

	total = nmemb * size;
	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (total / size != nmemb)
		return (NULL);
	out = malloc(total);
	if (!out)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)out;
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (out);
}
