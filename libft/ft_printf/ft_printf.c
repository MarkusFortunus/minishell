/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:03:51 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 11:00:08 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_get_format(char param, va_list ap)
{
	int	count;

	count = 0;
	if (param == 'c')
		count += ft_myputchar(va_arg(ap, int));
	if (param == 's')
		count += ft_myputstr(va_arg(ap, char *));
	if (param == 'd' || param == 'i')
		count += ft_myputnbr(va_arg(ap, int), 10, param);
	if (param == 'x' || param == 'X')
		count += ft_myputnbr(va_arg(ap, unsigned int), 16, param);
	if (param == 'u')
		count += ft_myputnbr(va_arg(ap, unsigned int), 10, param);
	if (param == 'p')
	{
		write(1, "0x", 2);
		count += (ft_printptr(va_arg(ap, unsigned long), 16) + 2);
	}
	if (param == '%')
		count += write(1, "%", 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list			ap;
	unsigned int	count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			count += ft_get_format(*++format, ap);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
