/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:21:21 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/20 16:54:35 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(char const *str, char c)
{
	size_t	count;
	size_t	check;

	count = 0;
	check = 0;
	while (*str)
	{
		if (*str != c && check == 0)
		{
			check = 1;
			count++;
		}
		else if (*str == c)
			check = 0;
		str++;
	}
	return (count);
}

static char	*ft_str_dup(const char *s1, size_t start, size_t end)
{
	char	*s_dup;
	size_t	i;

	i = 0;
	s_dup = malloc((end - start + 1) * sizeof(char));
	if (s_dup == NULL)
		return (NULL);
	while (start < end)
		s_dup[i++] = s1[start++];
	s_dup[i] = '\0';
	return (s_dup);
}

static char	**ft_free_array(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**ft_fill_array(char **array, const char *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			array[j] = ft_str_dup(s, index, i);
			if (!array[j])
				return (ft_free_array(array));
			j++;
			index = -1;
		}
		i++;
	}
	array[j] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = malloc((ft_count_word(s, c) + 1) * sizeof(char *));
	if (!s || array == NULL)
		return (NULL);
	array = ft_fill_array(array, s, c);
	return (array);
}
