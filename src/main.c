
#include "minishell.h"

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;
	
	if(!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

void	ft_parse_cmd(t_data *data)
{
	char	*str;

	i = 0;
	str = data->input;
	if (ft_check_quote_dollar(str, data->envp))
		data->args = ft_split_quote(data->input, "|");
	ft_parse_pipe(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;

	data = malloc(sizeof(t_data));
	data->envp = envp;
	if (isatty(STDIN_FILENO)) //fonction qui verifie si shell en mode interactive, mais pas util, on peut enlever
	{
		while (argc && argv)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, ft_handle_sigint);
			data->input = readline(PROMPT);
			if (data->input == NULL) //si ctrl+D, cela renvois EOF et readline renvoie null 
			{
				ft_printf("\nEXIT\n");
				break ;
			}
			else
			 	ft_history(data->input);
			ft_parse_cmd(data);
			free(data->input);//obligatoire sinon leaks!!
		}
		// ajouter fonction pour free historique
	}
	return (0);
	//else // shell no interactive ?	
	//free(data);
}