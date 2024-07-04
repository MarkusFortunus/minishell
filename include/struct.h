/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:30:57 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/04 15:23:38 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

//si pas d'utilisation de MAX-ARGS, recuperer argc max pour allouer mem pour argv et eargv
#ifndef MAX_ARGS
# define MAX_ARGS 10
#endif

# define EXEC    1
# define PIPE    2
# define REDIR   3
# define QUOTE   4
# define DQUOTE  5
# define APPEND  6
# define HEREDOC 7

typedef struct s_data
{
	char	*input;
	char	**args;
	char	**envp;
}			t_data;

typedef struct s_cmd
{
	int	type;
}		t_cmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}			t_pipecmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAX_ARGS];
	char	*eargv[MAX_ARGS];
}			t_execcmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	char	*efile;
	int		mode; //O_RDONLY, ..
	int		fd;
}			t_redircmd;

typedef struct s_quote
{
	int		type;
	t_cmd	*cmd;
	char	*str;
}			t_quote;

#endif
