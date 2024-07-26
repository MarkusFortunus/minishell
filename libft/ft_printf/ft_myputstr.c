/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myputstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:41:51 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 11:00:05 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_myputstr(char *s)
{
	int	count;

	if (s == NULL)
		return (write(1, "(null)", 6));
	count = 0;
	while (*s)
		count += write(1, s++, 1);
	return (count);
}
