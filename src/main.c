/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:20:03 by msimard           #+#    #+#             */
/*   Updated: 2024/07/04 10:46:45 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*static void	ft_parser(t_data *data)
{
	int		i;
	
	i = 0;
	char	*str = data->input;//obliger pour que le strtok fonctionne
	//checker si quote fermées
	
	int	quote = ft_check_quote(str);
	if (quote == 0)
	data->args = ft_split_cmd(data->input, '|'); //declarer un autre tableau pour stocker les token
	i = 0;
	token = ft_strtok(str, "| \"\'");
	while (token)
	{
		data->args[i] = token;//stocker les token au fur et a mesure dans un tableau (data->args)ou une liste chainée 
		ft_printf("%s\n", data->args[i]);
		i++;
		token = ft_strtok(NULL, "| \"\'");
	}
	while (data->args[i])
	{
		ft_printf("%s\n", data->args[i]);
		i++;
	}
	data->args[i] = NULL;
	free(data->args);
	ft_check_cmd(data);
}*/

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	 
	ft_init_signal();
	data = malloc(sizeof(t_data));
	data->envp = envp;
	if (isatty(STDIN_FILENO)) //fonction qui verifie si shell en mode interactive, mais pas util, on peut enlever
	{
		while (argc && argv)
		{
			data->input = readline(PROMPT);
			//ft_parser(data);
			ft_parsecmd(data->input);
			free(data->input);//obligatoire sinon leaks!!
		}
	}
	//else // shell no interactive ?
	//free(data);
}