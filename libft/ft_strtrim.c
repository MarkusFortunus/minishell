/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:50:33 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/17 10:58:30 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i <= len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;
	size_t	start;
	size_t	end;
	size_t	len;

	start = 0;
	if (ft_strlen(s1) == 0)
	{
		s1_trim = malloc(1);
		if (s1_trim == NULL)
			return (NULL);
		s1_trim[0] = '\0';
		return (s1_trim);
	}
	while (s1[start] && ft_strchr(set, s1[start]) != NULL)
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end]) != NULL)
		end--;
	len = end - start + 1;
	s1_trim = malloc(len + 1 * sizeof(char));
	if (s1_trim == NULL)
		return (NULL);
	ft_strncpy(s1_trim, s1 + start, len);
	return (s1_trim);
}
