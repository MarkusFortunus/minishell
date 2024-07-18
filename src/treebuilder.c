#include "minishell.h"

/*static void	print_node(t_cmd *node) //fonction pou debug a supprimer a la fin
{
	if (node == NULL)
	{
		ft_printf("Node is null\n");
		return ;
	}
	ft_printf("Type: %d\nAddress: %x\n", node->type, (void *)node);
}*/

t_cmd	*ft_build_exec_node(char **begin, char *end)
{
	t_execcmd	*cmd;
	size_t		count;
	
	count = ft_count_argc(begin, end);
	cmd = ft_calloc(1, sizeof(*cmd));//malloc pour la taille de l'execnode
	if (cmd == NULL)
		return (NULL);
	cmd->type = EXEC;
	cmd->argv = ft_calloc(count + 1, sizeof(char *));
	if (cmd->argv == NULL)
	{
		free (cmd);
		return (NULL);
	}
	cmd->eargv = ft_calloc(count + 1, sizeof(char *));
	if (cmd->eargv == NULL)
	{
		free(cmd->argv);
		free (cmd);
		return (NULL);
	}
	//print_node((t_cmd *)cmd);
	return ((t_cmd *)cmd); //casté car t_execcmd est une sous structure de cmd
}

t_cmd	*ft_build_pipe_node(t_cmd *left, t_cmd *right)
{
	t_pipecmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}

t_cmd	*ft_build_redir_node(int type, t_cmd *subcmd, char *file, char *efile)
{
	t_redircmd	*cmd;
	
	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = type;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = 0;//peut etre ne pas initialiser
	cmd->fd = 0;//idem
	//print_node((t_cmd *)cmd);
	return ((t_cmd *)cmd);
}