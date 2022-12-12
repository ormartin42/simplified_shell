/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:05:50 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:07:26 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_signal(int signum)
{
	if (signum == SIGINT)
	{
		if (g_g.fork)
			;
		else
		{
			g_g.signal = 1;
			ft_putchar_fd('\n', STDIN_FILENO);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			edit_var(&g_g.exitstatus, "?", "1");
		}
	}
	if (g_g.fork)
		;
	else
		signal(SIGQUIT, SIG_IGN);
}

void	init_signal(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_signal;
	g_g.signal = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
