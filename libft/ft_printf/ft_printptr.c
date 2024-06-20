/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:13:02 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 11:00:14 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(unsigned long n, unsigned int base)
{
	int		count;
	char	*digit;

	digit = "0123456789abcdef";
	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n < base)
		return (count + ft_myputchar(digit[n]));
	else
	{
		count = ft_printptr(n / base, base);
		return (count + ft_printptr(n % base, base));
	}
}
