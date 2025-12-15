/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:17:43 by dvavryn           #+#    #+#             */
/*   Updated: 2025/09/06 17:31:26 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*out;
	char	*cp;
	size_t	i;

	out = malloc(size);
	if (!out)
		return (NULL);
	if (ptr)
	{
		cp = (char *)ptr;
		i = 0;
		while (i < size)
		{
			out[i] = cp[i];
			i++;
		}
		free(ptr);
	}
	return ((void *)out);
}
