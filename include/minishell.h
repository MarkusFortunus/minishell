/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:59:55 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:14 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR "\001\033[0;34m\002\001\033[1m\002"
# define RES "\001\e[0m\022\002"
# define RED "\033[91m"
# define BLUE " \001\033\[33m\002\001\033[0;34m\002"
# define SYNTAX_TOKEN "syntax error near unexpected token 'newline'\n"
# define DIR ": is a directory\n"
# define FIL_DIR ": No such file or directory\n"
# define PIP "problem pipe\n"
# define PIP_REDI "problem redirecting pipes\n"

# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/ft_printf/ft_printf.h"
# include "../libft/libft.h"
# include "readline/history.h"
# include "readline/readline.h"
# include "struct.h"

int			ft_process_check_quote(char **str, int i, char type_of_quote, \
t_dol_qt *data);
void		verif_can_check_quote(char **str, t_dol_qt *data, int *i);
bool		each_pipe(t_pipe_cmd *p_data, t_data *data);
void		init_dol_qt(t_dol_qt *data, char **str, char **env);
bool		pipe_return_err(char **str, int i);
int			search_index(char type_of_char, char *str, int i);
void		replace_dollar_to_var(char **str, t_dol_qt *data, int i);
int			ft_check_quote_dollar(char **str, char **env);
int			ft_check_quote(char *str);
char		**ft_remove_quote__file(char **file, char **env);
int			ft_do_cmd(t_pipe_cmd *node, t_data *data);
int			stdin_file(t_pipe_cmd *p_data, t_data *data);
int			stdout_file(t_pipe_cmd *p_data);
bool		ft_heredoc(char *eof, t_pipe_cmd *data, t_data *ddata);
void		ft_execute(t_data *data, t_pipe_cmd *node);
char		*ft_search_path(char *command, char **envp);
int			ft_err_code(int exit_value);
void		ft_env_cmd(char **envp);
int			ft_exit_cmd(t_data *data, t_pipe_cmd *node, bool need_exit);
void		ft_pwd_cmd(void);
char		**ft_split_cmd(char *str, char sep);
char		**ft_get_envp_cpy(char **envp);
int			ft_chdir(char *path, t_pipe_cmd *node, t_data *data);
void		ft_unset(t_pipe_cmd *node, t_data *data);
bool		is_builtin(t_pipe_cmd *node);
int			ft_echo(t_pipe_cmd *node);
int			ft_export_cmd(t_pipe_cmd *node, t_data *data);
void		ft_export_tri(t_pipe_cmd *node, int y);
void		ft_export_search(char *export, char *name, t_pipe_cmd *node, \
t_data *data);
void		ft_export_modif(char *export, char ***env);
void		ft_export_add(char *export, char ***env);
int			ft_valid_name(char *str);
size_t		ft_eq_sign(char *str);
void		find_equal(char *str, int *equal_pos);
void		ft_free_data(t_data *data);
void		ft_free(char **to_free, char *exit);
int			ft_error(char *cmd, char *syntaxe, char *error, int exit_value);
void		ft_free_lst(t_pipe_cmd *node);
void		ft_free_exit(t_data *data, t_pipe_cmd *node);
void		ft_delete_hrd_file(void);
int			ft_count_arg(char **tab);
char		**ft_split_quote(char const *s, char *token);
int			ft_parse_cmd(t_data *data);
char		*ft_skip_quote(char *s);
char		*ft_skip_space(char *s);
int			ft_is_space(char *s);
int			ft_split_arg(t_pipe_cmd *node);
void		ft_fill_stdio_file(t_pipe_cmd *node, char *input);
int			ft_check_directory(t_pipe_cmd *node);
int			ft_check_pipe(t_data *data);
int			ft_get_index_cmd_arg(t_pipe_cmd *node);
int			ft_check_right(char *str);
int			ft_first_check_input(t_data *data);
void		ft_add_back(t_pipe_cmd **lst, t_pipe_cmd *new);
t_pipe_cmd	*ft_init_cmd_node(char *arg, int i, t_pipe_cmd *start_lst, \
t_data *data);
void		ft_init_redir_node(t_pipe_cmd *node);
bool		ft_pipe_return_err(char *str);
void		ft_count_redir(char *input, int *in, int *out);
int			ft_parse_pipe(t_data *data);
int			ft_parse_redir(t_pipe_cmd *node, char *input);
bool		ft_check_redir_syntax(char *input, t_pipe_cmd *node);
bool		start_pipe(t_pipe_cmd *p_data, t_data *data);
void		ft_handle_sigint(int signal);
void		ft_child_handler(int signal);
void		ft_heredoc_handler(int signal);

#endif