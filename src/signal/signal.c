#include "minishell.h"

void	ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_replace_line("\0", 0);
		rl_redisplay();
	}
}

void	ft_child_handler(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}

void	ft_heredoc_handler(int signal)
{
	(void)signal;
	//close fd et free donnée heredoc?
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	exit (1);
}
