/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:44:14 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/21 23:54:25 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check(char const c, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] != '\0' && check(s1[start], set))
		start++;
	end = 0;
	while (s1[end] != '\0')
		end++;
	while (end > start && check(s1[end - 1], set))
		end--;
	out = (char *)malloc((end - start + 1) * sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (start < end)
		out[i++] = s1[start++];
	out[i] = '\0';
	return (out);
}

static int	check(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
