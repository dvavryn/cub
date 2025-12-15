/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:49:51 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/11 02:24:01 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_calloc(size_t nmemb, size_t size)
{
	void			*out;
	size_t			total;
	size_t			i;
	unsigned char	*ptr;

	total = nmemb * size;
	if (!size || !nmemb)
		return (malloc(0));
	if (total / size != nmemb)
		return (NULL);
	out = malloc(total);
	if (!out)
		return (NULL);
	i = 0;
	ptr = (unsigned char *)out;
	while (i < total)
		ptr[i++] = 0;
	return (out);
}

char	*gnl_substr(const char *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	j = 0;
	while (s[j])
		j++;
	if (start >= j)
		len = 0;
	else if (start + len > j)
		len = j - start;
	out = (char *)gnl_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (i < len)
		out[i++] = s[start++];
	return (out);
}

char	*gnl_strjoin(const char *s1, const char *s2)
{
	char	*out;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = gnl_strlen(s1) + gnl_strlen(s2);
	out = gnl_calloc(len + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		out[i] = s2[j];
		i++;
		j++;
	}
	return (out);
}

char	*gnl_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*gnl_strdup(const char *s)
{
	char	*out;
	size_t	i;

	out = gnl_calloc(gnl_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	return (out);
}
