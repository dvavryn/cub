/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvavryn <dvavryn@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 23:59:54 by dvavryn           #+#    #+#             */
/*   Updated: 2025/05/22 00:08:28 by dvavryn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_puts(char *s);
int		ft_putnbr(int n);
int		ft_putunbr(unsigned int n);
int		ft_putnbr_hex(int c, unsigned int n);
int		ft_padress(void *p);
int		ft_putulong_hex(unsigned long n);

#endif