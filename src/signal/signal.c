/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:28:16 by fcornill          #+#    #+#             */
/*   Updated: 2024/09/13 16:39:17 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_replace_line("\0", 0);
		rl_redisplay();
		g_exit_stat = 1;
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
	ft_putchar_fd('\n', 1);
	rl_replace_line("\0", 0);
	exit(1);
}
