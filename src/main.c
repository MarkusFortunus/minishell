/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 13:24:33 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 16:28:46 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*user_toupper(char *env)
{
	char	*user;
	int		i;

	i = 0;
	user = ft_strchr(env, '=') + 1;
	while (user[i])
	{
		user[i] = ft_toupper(user[i]);
		i++;
	}
	return (user);
}

char	*printprompt(char **env, int i)
{
	char	*temp;
	char	*str;

	str = NULL;
	temp = ft_strdup(COLOR);
	while (env[i])
	{
		if (ft_strncmp(env[i], "USER", ft_strlen("USER")) == 0
			&& env[i][ft_strlen("USER")] == '=')
		{
			str = ft_strjoin(temp, COLOR);
			free(temp);
			temp = ft_strjoin(str, user_toupper(env[i]));
			free(str);
			str = ft_strjoin(temp, BLUE "\001\u25B7\002 ");
			free(temp);
			temp = ft_strjoin(str, RES);
			free(str);
			str = temp;
			return (str);
		}
		i++;
	}
	free(temp);
	return (NULL);
}

void	ft_history(char *cmd)
{
	HIST_ENTRY	*my_hist;

	if (!cmd || !*cmd)
		return ;
	add_history(cmd);
	my_hist = history_get(1);
}

int	ft_parse_cmd(t_data *data)
{
	if (ft_first_check_input(data) != 3)
		return (g_exit_stat);
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
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (ft_error(NULL, NULL, "error allocing memory\n", 2));
	data->envp = ft_get_envp_cpy(envp);
	data->prompt = printprompt(envp, 0);
	while (argc && argv)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_handle_sigint);
		data->input = readline(data->prompt);
		if (data->input == NULL)
			break ;
		else
			ft_history(data->input);
		ft_parse_cmd(data);
		free(data->input);
	}
	ft_free_data(data);
	rl_clear_history();
	return (0);
}
