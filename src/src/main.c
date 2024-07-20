
#include "minishell.h"

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;
	
	if(!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

void	ft_parse_redir(pipe_cmd_t *node)
{
	char	*s;

	s = node->cmd;
	while (*s)
	{
		if (*s == '>')
		{
			s++;
			if (*s == '>')
			{
				node->type = APPEND;
				s++;
			}
			else
				node->type = REDIR_O;
		}
		else if (*node->cmd == '<')
		{
			if (*s == '<')
			{
				node->type = HEREDOC;
				s++;
			}
			else
				node->type = REDIR_I;
		}
		s++;
	}
	ft_printf("%s %d\n", node->file_name, node->type);
}

pipe_cmd_t	*ft_init_cmd_node(char *arg, int i)
{
	pipe_cmd_t	*new_node;

	new_node = ft_calloc(1, sizeof(pipe_cmd_t));
	if (!new_node)
		return (NULL);
	new_node->cmd = arg;
	new_node->pos = i;
	ft_parse_redir(new_node);
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_back(pipe_cmd_t **lst, pipe_cmd_t *new)
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
	int		i;
	pipe_cmd_t	*new_node;
	pipe_cmd_t	*arg_lst = NULL;

	i = 0;
	str = data->input;
	if (ft_check_quote(str))
		data->args = ft_split_quote(data->input, "|");
	while (data->args[i])
	{
		new_node = ft_init_cmd_node(data->args[i], i);
		if (new_node)
			ft_add_back(&arg_lst, new_node);
		i++;
	}
	data->arg_count = i;
	pipe_cmd_t	*cur = arg_lst;
	while (cur)
	{
		ft_check_cmd(data, cur);
		cur = cur->next;
	}
	cur = arg_lst;
    while (cur) { //remplacer par fonction pour free lst
        pipe_cmd_t *next = cur->next;
        free(cur->cmd);
        free(cur);
        cur = next;
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