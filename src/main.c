
#include "minishell.h"

char *user_toupper(char *env)
{
	char *user;
	int i;

	i = 0;
	user = ft_strchr(env, '=') + 1;
	while (user[i])
	{
		user[i] = ft_toupper(user[i]);
		i++;
	}
	return user;
}

char *printprompt(char **env)
{
	int i = 0;
	char *temp = NULL; // Duplicate COLOR
	char *str = ft_strdup(COLOR);
	while (env[i])
    {
        if (strncmp(env[i], "USER", ft_strlen("USER")) == 0 && env[i][ft_strlen("USER")] == '=')
        {
			temp = ft_strjoin(str, EMOJI);
			free(str);
			str = ft_strjoin(temp, COLOR);
			free(temp);
			temp = ft_strjoin(str, user_toupper(env[i]));
			free(str); 
			str = ft_strjoin(temp, BLUE"\u25B7 ");
			free(temp);
			temp = ft_strjoin(str, RES);
			free(str);
			str = temp;
            return str;
        }
        i++;
    }
	free(temp);
	return "YOU";
}

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;
	
	if(!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

int	ft_parse_cmd(t_data *data)
{
	if (ft_first_check_input(data) != 3)
		return (exit_stat);
	if (ft_strlen(data->input) == 0)
		return (1);
	else
		data->args = ft_split_quote(data->input, "|");
	if (!data->args)
		ft_free(data->args, NULL);
	if (ft_check_pipe(data))
		return (EXIT_FAILURE);
	if (ft_parse_pipe(data))
		return (EXIT_FAILURE);
	// ft_free(data->args, NULL);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data			*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return ft_error(NULL, NULL, "error allocing memory\n", 2);
	data->envp = ft_get_envp_cpy(envp);
	data->prompt = printprompt(envp);
	// if (isatty(STDIN_FILENO)) //fonction qui verifie si shell en mode interactive, mais pas util, on peut enlever
	// { ///a commenter pour le testeur!!!
		while (argc && argv)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, ft_handle_sigint);
			//data->input = readline("\001\033[32m\002MINISHELL\001\e[0m\022\002");
			data->input = readline(data->prompt);
			// data->input = readline(">");
			if (data->input == NULL) //si ctrl+D, cela renvois EOF et readline renvoie null 
				break ;
			else
			 	ft_history(data->input);
			ft_parse_cmd(data);
			free(data->input);//obligatoire sinon leaks!!
		}
		// ajouter fonction pour free historique
	// }
	rl_clear_history();
	ft_free_data(data);
	rl_clear_history();
	return (0);
	//else // shell no interactive ?	
	
}