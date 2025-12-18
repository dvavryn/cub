/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:41:59 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/18 01:06:08 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	digits(int n);
static void		pos(char *str, int n, size_t len);
static void		neg(char *str, int n, size_t *len);

char	*ft_itoa(int n)
{
	size_t	len;
	char	*out;

	len = digits(n);
	if (n <= 0)
		len++;
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[len] = '\0';
	if (n == 0)
		out[0] = '0';
	if (n < 0)
		neg(out, n, &len);
	else
		pos(out, n, len);
	return (out);
}

static size_t	digits(int n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	pos(char *out, int n, size_t len)
{
	while (n != 0)
	{
		len--;
		out[len] = (n % 10) + '0';
		n /= 10;
	}
}

static void	neg(char *out, int n, size_t *len)
{
	out[0] = '-';
	if (n == -2147483648)
	{
		(*len)--;
		out[*len] = '8';
		n = -(n / 10);
	}
	else
		n = -n;
	pos(out, n, *len);
}
