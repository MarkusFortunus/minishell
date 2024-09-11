/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:26:03 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/05 15:37:38 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_handle_output_redirection(char *input, int *i, t_pipe_cmd *node,
		int *out_index)
{
	int	out;

	out = 1;
	while (input[++(*i)] == '>')
		out++;
	if (input[*i] == ' ' || input[*i] == '\t')
		*i = ft_skip_space(&input[*i]) - input;
	if ((input[*i] == '<' || input[*i] == '>') && ft_error(NULL, NULL,
			"syntax error near unexpected token 'newline'\n", 2))
		return (false);
	if (out > 2 && ft_error(NULL, NULL,
			"syntax error near unexpected token '>>'\n", 2))
		return (false);
	if (out == 2)
		node->trunc[*out_index] = true;
	else if (out == 1)
		node->trunc[*out_index] = false;
	(*out_index)++;
	return (true);
}

static bool	ft_handle_input_redirection(char *input, int *i, t_pipe_cmd *node,
		int *in_index)
{
	int	in;

	in = 1;
	while (input[++(*i)] == '<')
		in++;
	if (input[*i] == ' ' || input[*i] == '\t')
		*i = ft_skip_space(&input[*i]) - input;
	if ((input[*i] == '>' || input[*i] == '<') && ft_error(NULL, NULL,
			"syntax error near unexpected token 'newline'\n", 2))
		return (false);
	if (in > 2 && ft_error(NULL, NULL,
			"syntax error near unexpected token '<<'\n", 2))
		return (false);
	if (in == 2)
		node->heredoc[*in_index] = true;
	else if (in == 1)
		node->heredoc[*in_index] = false;
	(*in_index)++;
	return (true);
}

bool	ft_check_redir_syntax(char *input, t_pipe_cmd *node)
{
	int		i;
	int		out_index;
	int		in_index;
	bool	return_var;

	return_var = true;
	i = 0;
	out_index = 0;
	in_index = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i = ft_skip_quote(&input[i]) - input;
		if (input[i] == '>')
			return_var = ft_handle_output_redirection(input, &i, node,
					&out_index);
		else if (input[i] == '<')
			return_var = ft_handle_input_redirection(input, &i, node,
					&in_index);
		else if (input[i])
			i++;
		if (!return_var)
			return (false);
	}
	return (return_var);
}
