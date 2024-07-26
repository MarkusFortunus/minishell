/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:57:43 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 10:58:35 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new_str;
	size_t	i;

	i = 0;
	if (!s || ft_strlen(s) == 0 || start >= ft_strlen(s))
	{
		new_str = malloc(1);
		if (new_str == NULL)
			return (NULL);
		new_str[i] = '\0';
		return (new_str);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new_str = malloc((len + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (i < len)
	{
		new_str[i] = s[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
