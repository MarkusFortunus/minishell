#include "minishell.h"

static char	*ft_str_dup(char *input, int start, int end)
{
	char	*s_dup;
	int		i;

	i = 0;
	s_dup = ft_calloc((end - start + 1), sizeof(char));
	if (!s_dup)
		return (NULL);
	while (start < end)
		s_dup[i++] = input[start++];
	s_dup[i] = '\0';
	return (s_dup);
}

static void	ft_fill_stdout_file(pipe_cmd_t *node, char *input, int *i, int *i_o)
{
	int	start;

	while (input[*i] == '>')
		input[(*i)++] = ' ';
	*i = ft_skip_space(&input[*i]) - input;
	if (input[*i])
	{
		start = *i;
		if (input[*i] == '\'' || input[*i] == '"')
			*i = ft_skip_quote(&input[*i]) - input;
		else
		{
			while (input[*i] && (input[*i] != ' ' && input[*i] != '\t'
					&& input[*i] != '>' && input[*i] != '<'))
				(*i)++;
		}
		node->stdout_file[*i_o] = ft_str_dup(input, start, *i);
		if (!node->stdout_file[*i_o])
			return (ft_free(node->stdout_file, NULL));
		(*i_o)++;
		while (start < *i)
			input[start++] = ' ';
	}
}

static void	ft_fill_stdin_file(pipe_cmd_t *node, char *input, int *i, int *i_in)
{
	int	start;

	while (input[*i] == '<')
		input[(*i)++] = ' ';
	*i = ft_skip_space(&input[*i]) - input;
	if (input[*i])
	{
		start = *i;
		if (input[*i] == '\'' || input[*i] == '"')
			*i = ft_skip_quote(&input[*i]) - input;
		else
		{
			while (input[*i] && (input[*i] != ' ' && input[*i] != '\t'
					&& input[*i] != '>' && input[*i] != '<'))
				(*i)++;
		}
		node->stdin_file[*i_in] = ft_str_dup(input, start, *i);
		if (!node->stdin_file[*i_in])
			return (ft_free(node->stdin_file, NULL));
		(*i_in)++;
		while (start < *i)
			input[start++] = ' ';
	}
}

void	ft_fill_stdio_file(pipe_cmd_t *node, char *input)
{
	int	i;
	int	index_out;
	int	index_in;

	i = 0;
	index_out = 0;
	index_in = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
			i = ft_skip_quote(&input[i]) - input;
		else if (input[i] == '>')
			ft_fill_stdout_file(node, input, &i, &index_out);
		else if (input[i] == '<')
			ft_fill_stdin_file(node, input, &i, &index_in);
		else
			i++;
	}
	if (node->stdout_file)
		node->stdout_file[index_out] = 0;
	if (node->stdin_file)
		node->stdin_file[index_in] = 0;
	node->cmd = input;
}
