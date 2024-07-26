/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:19:52 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 10:59:55 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_myputnbr(long n,	int base, char param)
{
	int		count;
	char	*digit;

	if (param == 'X')
		digit = "0123456789ABCDEF";
	else
		digit = "0123456789abcdef";
	count = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n < 0)
	{
		write(1, "-", 1);
		return (ft_myputnbr(-n, base, param) + 1);
	}
	if (n < base)
		return (count + ft_myputchar(digit[n]));
	else
	{
		count = ft_myputnbr(n / base, base, param);
		return (count + ft_myputnbr(n % base, base, param));
	}
}
