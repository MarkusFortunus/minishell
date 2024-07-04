/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treebuilder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:49:32 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/04 15:24:35 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_node(t_cmd *node)
{
	if (node == NULL)
	{
		ft_printf("Node is null\n");
		return ;
	}
	ft_printf("Type: %d\nAddress: %x\n", node->type, (void *)node);
}

t_cmd	*ft_build_exec_node(void)
{
	t_execcmd	*cmd;
	
	cmd = ft_calloc(1, sizeof(*cmd));//malloc pour la taille de l'execnode
	if (cmd == NULL)
		return (NULL);
	cmd->type = EXEC;
	print_node((t_cmd *)cmd);
	return ((t_cmd *)cmd); //casté car t_execcmd est une sous structure de cmd
}

t_cmd	*ft_build_pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	print_node((t_cmd *)cmd);
	return ((t_cmd *)cmd);
}

t_cmd	*ft_build_redir_node(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redircmd	*cmd;
	
	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	print_node((t_cmd *)cmd);
	return ((t_cmd *)cmd);
}