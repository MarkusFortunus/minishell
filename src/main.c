/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:20:03 by msimard           #+#    #+#             */
/*   Updated: 2024/06/20 13:39:52 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


static void	parser(t_data *data)
{
	//fonction pour checker les quotes

	int	i;
	
	char	*token = "|<>"; //ajouter un flag approprier par token
	char	*str = data->input;//obliger pour que le strtok fonctionne
	data->args = ft_calloc(1024, sizeof(char *)); //declarer un autre tableau pour stocker les token
	token = ft_strtok(str, "|<>");
	i = 0;
	while (token)
	{
		data->args[i] = token;//stocker les token au fur et a mesure dans un tableau (data->args)ou une liste chainée 
		ft_printf("%s\n", data->args[i]);
		i++;
		token = ft_strtok(NULL, "|<>");
	}
	ft_printf("%d\n", i);
	data->args[i] = NULL;
	free(data->args);
	check_cmd(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	init_signal();
	data = malloc(sizeof(t_data));
	data->envp = envp;
	if (isatty(STDIN_FILENO)) //fonction qui verifie si shell en mode intecractive, mais pas util, on peut enlever
	{
		while (argc && argv)
		{
			data->input = readline(PROMPT);
			parser(data);
			//check_cmd(data);
			free(data->input);//obligatoire sinon leaks!!
		}
	}
	//else // shell no interactive ?
	//free(data);
}