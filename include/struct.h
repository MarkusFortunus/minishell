/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:30:57 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/09 11:05:36 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define EXEC    1
# define PIPE    2
# define REDIR   3
# define APPEND  4
# define HEREDOC 5

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
	char	**argv;
	char	**eargv;
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


#endif
