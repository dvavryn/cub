/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:07:59 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/21 23:54:49 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	count_words(char const *s, char c);
static char		*cpy(char *out, char const *s, char c, size_t *index);
static void		free_all(char **out, size_t i);
static size_t	len(char const *s, char c, int index);

char	**ft_split(char const *s, char c)
{
	char	**out;
	size_t	i;
	size_t	index;

	if (!s)
		return (NULL);
	out = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count_words(s, c))
	{
		while (s[index] == c)
			index++;
		out[i] = (char *)malloc((len(s, c, index) + 1) * sizeof(char));
		if (!out[i])
		{
			free_all(out, i);
			return (NULL);
		}
		cpy(out[i++], s, c, &index);
	}
	out[i] = NULL;
	return (out);
}

static size_t	len(char const *s, char c, int index)
{
	int	i;

	i = 0;
	while (s[index] != c && s[index] != '\0')
	{
		index++;
		i++;
	}
	return (i);
}

static void	free_all(char **out, size_t i)
{
	while (i > 0)
	{
		i--;
		free(out[i]);
	}
	free(out);
}

static char	*cpy(char *out, char const *s, char c, size_t *index)
{
	size_t	i;

	i = 0;
	while (s[*index] != c && s[*index] != '\0')
	{
		out[i] = s[*index];
		i++;
		(*index)++;
	}
	out[i] = '\0';
	return (out);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}
