/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onault <onault@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:03:54 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 17:04:48 by onault           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

int						g_exit_stat;

typedef struct s_dol_qt
{
	int					ienv;
	int					return_var;
	char				*str_start;
	char				**env;
	int					end_double;
	int					end_single;
}						t_dol_qt;

/**
 * @param input String of command
 * @param args arguments
 * @param envp Environement
 * @param fd pipe file descriptor
 * @param pid ID process for fork
 * @param arg_count number of arguments
 * */
typedef struct s_data
{
	char				*prompt;
	char				*input;
	char				**args;
	char				**envp;
	int					arg_count;
	char				*file;
	pid_t				pid;
	int					*pidt;
	int					fd[2];
	int					prev;
}						t_data;

/**
 * @param x index de cmd_arg
 **/
typedef struct s_pipe_cmd
{
	char				*error;
	int					err_to_return ;
	char				**env;
	char				**stdin_file;
	char				**stdout_file;
	int					stdin_count;
	int					stdout_count;	
	char				**cmd_arg;
	int					pos;
	char				*cmd;
	int					arg_cnt;
	bool				*trunc;
	bool				*heredoc;
	struct s_pipe_cmd	*next;
	struct s_pipe_cmd	*start_ls;
	int					x;
	int					stdin;
	int					stdout;
	int					eof_nb;
}						t_pipe_cmd;

/**
 * @param tmp_file temporary file name
 * @param filename final file name
 * @param fd file descriptor int
 * @param id process id
 * @param status return status of child, in waitpid
 **/
typedef struct s_heredoc
{
	char				*tmp_file;
	char				*filename;
	int					fd;
	int					id;
	int					status;
}						t_heredoc;

#endif
