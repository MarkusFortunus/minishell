/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:25:59 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 10:55:46 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *d, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	return (d);
}

static int	ft_get_len(int n)
{
	int	lenght;

	lenght = 1;
	if (n < 0)
	{
		n = n * -1;
		lenght++;
	}
	while (n > 9)
	{
		n = n / 10;
		lenght++;
	}
	return (lenght);
}

static void	ft_fill_str(char *str, int n, int len)
{
	int	sign;
	int	i;

	i = 0;
	sign = 0;
	if (n < 0)
	{
		n = n * -1;
		sign = 1;
	}
	str[len] = '\0';
	i = len - 1;
	while (i >= sign)
	{
		str[i--] = (n % 10) + 48;
		n = n / 10;
	}
	if (sign)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
	{
		str = malloc(12 * sizeof(char));
		if (str != NULL)
			ft_strcpy(str, "-2147483648");
		return (str);
	}
	len = ft_get_len(n);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_fill_str(str, n, len);
	return (str);
}
