/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:01:55 by fcornill          #+#    #+#             */
/*   Updated: 2024/08/21 14:36:25 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s_dup;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1) + 1;
	s_dup = ft_calloc(len, sizeof(char));
	if (s_dup == NULL)
		return (NULL);
	ft_strcpy(s_dup, s1);
	return (s_dup);
}
