/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 12:04:36 by fcornill          #+#    #+#             */
/*   Updated: 2024/04/15 18:11:07 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*lastnod;
	int		i;
	int		j;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_del(lst));
	lastnod = ft_lstlast(lst);
	i = 0;
	j = 0;
	while (lastnod->content[i] != '\0' && lastnod->content[i] != '\n')
		i++;
	while (lastnod->content[i] != '\0' && lastnod->content[++i])
		buf[j++] = lastnod->content[i];
	buf[j] = '\0';
	ft_del(lst);
	lst_add_back(lst, buf);
}

char	*new_line(t_list **lst, char *line, int len)
{
	t_list	*tmp;
	int		i;

	tmp = *lst;
	i = 0;
	len = len + lst_strlen(tmp);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (ft_del(lst), NULL);
	i = lst_cpy(tmp, line, i);
	line[len] = '\0';
	return (line);
}

void	lst_add_back(t_list **lst, char *buf)
{
	t_list	*new_node;
	t_list	*tmp;

	if (!buf[0])
		return (free(buf));
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buf);
		return (ft_del(lst));
	}
	tmp = ft_lstlast(lst);
	if (!tmp)
		*lst = new_node;
	else
		tmp->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

void	ft_lstnew(t_list **lst, int fd)
{
	int		char_read;
	char	*buf;

	char_read = 0;
	while (!lst_strchr(*lst))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
			return (ft_del(lst));
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		lst_add_back(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst[FD_MAX];
	char			*next_line;
	int				len;

	next_line = NULL;
	len = 0;
	if (read(fd, &next_line, 0) < 0)
		return (ft_del(&lst[fd]), NULL);
	if (fd < 0 || fd > (FD_MAX - 1) || BUFFER_SIZE <= 0)
		return (NULL);
	ft_lstnew(&lst[fd], fd);
	if (lst[fd] == NULL)
		return (NULL);
	next_line = new_line(&lst[fd], next_line, len);
	if (lst[fd] == NULL)
		return (NULL);
	ft_lstclear(&lst[fd]);
	return (next_line);
}
