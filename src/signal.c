
#include "minishell.h"

void	ft_handle_sigint(int signal)
{

	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_child_handle_signal(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', 1);
	rl_redisplay();
}