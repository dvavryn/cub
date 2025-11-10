/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:24:50 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/24 23:31:00 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*out;
	size_t	i;

	if (!s || !n)
		return (NULL);
	out = (char *)malloc((n + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < n)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = 0;
	return (out);
}
