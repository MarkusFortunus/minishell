/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:21:27 by msimard           #+#    #+#             */
/*   Updated: 2024/07/09 15:11:20 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define GREEN "\033[92m"
# define RES "\033[0m"
# define RED "\033[91m"
# define PROMPT GREEN"minishell$ "RES

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "../libft/ft_printf/ft_printf.h"
#include "struct.h"

void	ft_check_cmd(t_data *data);
void	ft_env_cmd(char **envp);
void	ft_export_cmd(t_data *data);
void	ft_exit_cmd(t_data *data);
void	ft_pwd_cmd();
int		ft_check_quote(char *str);
char	**ft_split_cmd(char *str, char sep);
void	ft_init_signal(void);
char	**ft_get_envp_cpy(char	**envp);
char	*ft_strtok(char *str, const char *sep);
void	ft_execute(char *commands, char **envp);
char	*ft_search_path(char *command, char **envp);
void	ft_free(char **to_free, char *exit);
void	ft_error(char *error);
void	ft_isbuilt(char **list);
size_t	ft_count_argc(char **begin, char *end);


//test

int			ft_add_token(char **begin, char *end, char **old, char **end_old);
int			ft_check_token(char	**begin, char *end, char *tok);
t_cmd		*ft_parsecmd(char *s);
t_cmd		*ft_parseexec(char **begin, char *end);
t_cmd		*ft_parseredir(t_cmd *cmd, char **begin, char *end);
//t_cmd		*ft_parseline(char **begin, char *end);
t_cmd		*ft_parsepipe(char **begin, char *end);
t_cmd		*ft_build_pipe_node(t_cmd *left, t_cmd *right);
t_cmd		*ft_build_exec_node(size_t count);
t_cmd		*ft_nulterminate_str(t_cmd *cmd);
t_cmd		*ft_build_redir_node(int type, t_cmd *subcmd, char *file, char *efile);

#endif