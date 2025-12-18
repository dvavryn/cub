/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 23:52:27 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/25 00:03:19 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoinc(char *str, int c)
{
	char	*out;
	size_t	i;
	size_t	j;

	if (!str || !c)
		return (NULL);
	i = ft_strlen(str);
	out = (char *)malloc(i + 2);
	if (!out)
		return (NULL);
	j = 0;
	while (j < i)
	{
		out[j] = str[j];
		j++;
	}
	out[j] = c;
	out[j + 1] = 0;
	return (out);
}
