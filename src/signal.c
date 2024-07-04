/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimard <msimard@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:16:01 by fcornill          #+#    #+#             */
/*   Updated: 2024/06/24 14:38:29 by msimard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaddset(&sa.sa_mask, SIGINT);
	//sa.sa_sigaction = &handle_sigint;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit (EXIT_FAILURE);
}