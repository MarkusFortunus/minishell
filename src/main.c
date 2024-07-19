
#include "minishell.h"

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;
	
	if(!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

pipe_cmd_t	*init_cmd_node(char *arg, int i)
{
	pipe_cmd_t	*new_node;

	new_node = malloc(sizeof(pipe_cmd_t));
	if (!new_node)
		return (NULL);
	new_node->cmd = arg;
	new_node->pos = i;
	//check_if_redir
	new_node->next = NULL;
	return (new_node);
}

void	ft_pipe_cmd_add_back(pipe_cmd_t **lst, pipe_cmd_t *new)
{
	pipe_cmd_t	*tmp;

	tmp = *lst;
	if (new == NULL)
		return ;
	new->next = NULL;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}



static void	ft_parser(t_data *data)
{
	char	*str;
	int		check;
	int		i;
	pipe_cmd_t	*ecmd = NULL;

	i = 0;
	str = data->input;
	check = ft_check_quote(str);
	if (check)
		data->args = ft_split(data->input, '|');
	// 	ft_get_cmd(ft_parsecmd(data->input), data);
	while (data->args[i])
	{
		pipe_cmd_t *new_node = init_cmd_node(data->args[i], i);
		ft_pipe_cmd_add_back(&ecmd, new_node);
		i++;
	}
	data->arg_count = i;
	pipe_cmd_t *current = ecmd;
    while (current != NULL)
    {
        ft_check_cmd(data, current);
        current = current->next;
		//free au fur et a mesure ?
    }
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	 
	signal(SIGQUIT, SIG_IGN);
	ft_init_signal();
	data = malloc(sizeof(t_data));
	data->envp = envp;
	if (isatty(STDIN_FILENO)) //fonction qui verifie si shell en mode interactive, mais pas util, on peut enlever
	{
		while (argc && argv)
		{
			data->input = readline(PROMPT);
			if (data->input == NULL)
			{
				ft_printf("\nEXIT\n");
				break ;
			}
			else
			 	ft_history(data->input);
			ft_parser(data);
			free(data->input);//obligatoire sinon leaks!!
		}
		// ajouter fonction pour free historique
	}
	return (0);
	//else // shell no interactive ?
	//free(data);
}