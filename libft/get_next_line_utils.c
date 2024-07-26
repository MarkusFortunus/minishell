/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 15:28:26 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/15 18:11:37 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
		return (temp);
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

int	lst_strchr(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n' || lst->content[i] == '\0')
				return (1);
			++i;
		}
		lst = lst->next;
	}
	return (0);
}

int	lst_strlen(t_list *temp)
{
	int	i;
	int	k;

	k = 0;
	i = 0;
	while (temp)
	{
		i = 0;
		while (temp->content[i])
		{
			if (temp->content[i] == '\n')
				return (++k);
			++i;
			++k;
		}
		temp = temp->next;
	}
	return (k);
}

int	lst_cpy(t_list *temp, char *line, int index)
{
	int	i;

	while (temp)
	{
		i = 0;
		while (temp->content[i] != '\0')
		{
			if (temp->content[i] == '\n')
				return (line[index++] = temp->content[i]);
			else
				line[index++] = temp->content[i++];
		}
		temp = temp->next;
	}
	return (index);
}

void	ft_del(t_list **lst)
{
	t_list	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}
