/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:21:27 by msimard           #+#    #+#             */
/*   Updated: 2024/06/20 10:47:19 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[92m"
# define RES "\033[0m"
# define PROMPT GREEN"minishell$ "RES

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"

typedef struct s_data
{
	char	*input;
	char	**args;
	char	**envp;
}			t_data;

typedef struct s_token
{
	int		pipe;
	int		right;
	int		left;
	int		heredoc;
	int		append;
}			t_token;

/*typedef struct s_list
{
	char			*cmd;
	char			**arg;
	struct s_list	*next; //pointeur vers le noeud suivant
}				t_list;*/

void	check_cmd(t_data *data);
void	env_cmd(char **envp);
void	export_cmd(t_data *data);
void	exit_cmd(t_data *data);
void	pwd_cmd();
void	get_token(t_data *data, t_token *token);
void	get_flag(char *str, t_token *token);
void	init_signal(void);
char	**get_envp_cpy(char	**envp);
char	*ft_strtok(char *str, const char *sep);


#endif