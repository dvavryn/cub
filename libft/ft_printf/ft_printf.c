/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:48:08 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/19 17:25:53 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	conversions(va_list args, char c);

int	ft_printf(const char *format, ...)
{
	size_t	i;
	va_list	args;
	int		l;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	l = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			l += conversions(args, format[i]);
		}
		else
			l += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (l);
}

static int	conversions(va_list args, char c)
{
	size_t	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(args, int));
	if (c == 's')
		i += ft_puts(va_arg(args, char *));
	if (c == 'p')
		i += ft_padress(va_arg(args, void *));
	if (c == 'd')
		i += ft_putnbr(va_arg(args, int));
	if (c == 'i')
		i += ft_putnbr(va_arg(args, int));
	if (c == 'u')
		i += ft_putunbr(va_arg(args, unsigned int));
	if (c == 'x')
		i += ft_putnbr_hex('x', va_arg(args, unsigned int));
	if (c == 'X')
		i += ft_putnbr_hex('X', va_arg(args, unsigned int));
	if (c == '%')
		i += ft_putchar('%');
	return (i);
}
