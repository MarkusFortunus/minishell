/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcornill <fcornill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:16:01 by fcornill          #+#    #+#             */
/*   Updated: 2024/07/10 14:57:52 by fcornill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	handle_sigint(int signal, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signal == SIGINT)
	{
		
	}
}

void	ft_init_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	//sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	sigaction(SIGINT, &sa, NULL);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit (EXIT_FAILURE);
}