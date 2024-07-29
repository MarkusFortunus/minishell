#include "../include/minishell.h"

//Error function, print error message and exit
void	ft_error(char *error, int exit_value)
{
	write(2, RED, ft_strlen(RED));
	write(2, "Error:\n", 8);
	write(2, error, ft_strlen(error));
	write(2, RES, ft_strlen(RES));
	exit(exit_value);
}



// void	ft_check_redir_syntax(char *input, pipe_cmd_t *node)
// {
// 	int	i;
// 	int	out;
// 	int	in;
// 	// int	trunc_index = 0;
// 	// int	heredoc_index = 0;
// 	int redir_index = 0;

// 	i = 0;
// 	out = 0;
// 	in = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' || input[i] == '"') // Check for quotes
// 		{
// 			input = ft_skip_quote(&input[i]); // Skip the quoted part
// 			i = input - input; // Adjust the index
// 		}
// 		if (input[i] == '>')
// 		{
// 			out++;
// 			while (input[++i] == '>')
// 				out++;
// 			if (input[i] == ' ' || input[i] == '\t')
// 			{
// 				while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 					i++;
// 			}
// 			if (input[i] == '<')
// 				ft_error("syntax error near unexpected token 'newline'\n", 2);
// 			if (out > 2)
// 				ft_error("syntax error near unexpected token '>>'\n", 2);
// 			if (out == 2)
// 			{
// 				//node->trunc[trunc_index] = true;
// 				node->redir_type[redir_index] = APPEND;
// 			}
// 			else if (out == 1)
// 				node->redir_type[redir_index] = REDIR_OUTPUT;
// 				//node->trunc[trunc_index] = false;
// 			//trunc_index++;
// 			redir_index++;
// 			out = 0;
// 		}
// 		else if (input[i] == '<')
// 		{
// 			in++;
// 			while (input[++i] == '<')
// 				in++;
// 			if (input[i] == ' ' || input[i] == '\t')
// 			{
// 				while (input[i] && (input[i] == ' ' || input[i] == '\t'))
// 					i++;
// 			}
// 			if (input[i] == '>')
// 				ft_error("syntax error near unexpected token 'newline'\n", 2);
// 			if (in > 2)
// 				ft_error("syntax error near unexpected token '<<'\n", 2);
// 			if (in == 2)
// 				node->redir_type[redir_index] = HEREDOC;
// 				//node->heredoc[heredoc_index] = true;
// 			else if (in == 1)
// 				node->redir_type[redir_index] = REDIR_INPUT;
// 				// node->heredoc[heredoc_index] = false;
// 			//heredoc_index++;
// 			redir_index++;
// 			in = 0;
// 		}
// 		else
// 			i++;
// 	}
// }

void ft_handle_output_redirection(char *input, int *i, int *redir_index, pipe_cmd_t *node)
{
    int out = 1;
    while (input[++(*i)] == '>')
        out++;
    while (input[*i] == ' ' || input[*i] == '\t')
        (*i)++;
    if (input[*i] == '<')
        ft_error("syntax error near unexpected token 'newline'\n", 2);
    if (out > 2)
        ft_error("syntax error near unexpected token '>>'\n", 2);
    if (out == 2)
        node->redir_type[(*redir_index)++] = APPEND;
    else if (out == 1)
        node->redir_type[(*redir_index)++] = REDIR_OUTPUT;
}

void ft_handle_input_redirection(char *input, int *i, int *redir_index, pipe_cmd_t *node)
{
    int in = 1;
    while (input[++(*i)] == '<')
        in++;
    while (input[*i] == ' ' || input[*i] == '\t')
        (*i)++;
    if (input[*i] == '>')
        ft_error("syntax error near unexpected token 'newline'\n", 2);
    if (in > 2)
        ft_error("syntax error near unexpected token '<<'\n", 2);
    if (in == 2)
        node->redir_type[(*redir_index)++] = HEREDOC;
    else if (in == 1)
        node->redir_type[(*redir_index)++] = REDIR_INPUT;
}

void ft_check_redir_syntax(char *input, pipe_cmd_t *node)
{
    int i = 0;
    int redir_index = 0;

    while (input[i])
    {
        if (input[i] == '\'' || input[i] == '"')
        {
            input = ft_skip_quote(&input[i]);
        }
        else if (input[i] == '>')
        {
            ft_handle_output_redirection(input, &i, &redir_index, node);
        }
        else if (input[i] == '<')
        {
            ft_handle_input_redirection(input, &i, &redir_index, node);
        }
        else
        {
            i++;
        }
    }
}

//Free un tableau. Exit si un message est ajouter. Sinon, mettre "NULL"
void	ft_free(char **to_free, char *exit)
{
	int	i;

	if (!to_free)
		return ;
	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
	if (exit)
		ft_error(exit, 1); // passss surrrrr
}
