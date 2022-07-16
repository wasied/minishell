/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbennafl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 20:47:05 by mbennafl          #+#    #+#             */
/*   Updated: 2022/07/16 18:18:55 by mbennafl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler()
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (!g_pid)
		rl_redisplay();
}

static void	sigquit_handler()
{
	if (g_pid)
	{
		kill(g_pid, SIGQUIT); // PROTECT
		ft_putstr_fd(STDOUT_FILENO, "Quit: 3\n");
	}
	else
		ft_putstr_fd(STDOUT_FILENO, "\b \b");
}

void	signals_init()
{
	signal(SIGINT, sigint_handler);	// ERROR IF == SIG_ERR
	signal(SIGQUIT, sigquit_handler);	// ERROR IF == SIG_ERR
}
