
#include "minishell.h"

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;
	
	if(!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

static void	ft_parser(t_data *data)
{
	char	*str;
	int		check;

	str = data->input;
	check = ft_check_quote(str);
	if (check)
	{
		if (fork() == 0)
			ft_get_cmd(ft_parsecmd(data->input), data);
		wait(NULL);
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