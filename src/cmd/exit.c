#include "minishell.h"

void	ft_exit_cmd(t_data *data, pipe_cmd_t *node, bool need_exit)
{
	//use node
	if (data->arg_count > 1)
	{
		free(data->fd);
		ft_free_lst(node->start_ls);
	}
	else
		ft_free_lst(node);
	free(data->input);//sinon leaks dans le cas ou on ne tape de commande valide
	ft_free_data(data);
	if (need_exit)
		exit (EXIT_SUCCESS);
	return ;
}
