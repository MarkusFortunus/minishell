#include "minishell.h"

//Error function, print error message and exit
int	ft_error(char *cmd, char *syntaxe, char *error, int exit_value)
{
	write(2, RED, ft_strlen(RED));
	if (cmd)
		write(2, cmd, ft_strlen(cmd));
	else
		write(2, "Error:\n", 8);
	write(2, error, ft_strlen(error));
	if (syntaxe)
		write(2, syntaxe, ft_strlen(syntaxe));
	write(2, RES, ft_strlen(RES));
	return (exit_stat = exit_value);
}

int	ft_err_code(int exit_value)
{
	if (WIFEXITED(exit_value))
		exit_stat = WEXITSTATUS(exit_value);
	if (WIFSIGNALED(exit_value))
		exit_stat = (128 + WTERMSIG(exit_value));
	return (exit_stat);
}
