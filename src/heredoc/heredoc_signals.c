/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:50:57 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:51:11 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDIN_FILENO);
		edit_var(&g_g.exitstatus, "?", "1");
		exit(1);
	}
}

void	ft_init_heredoc_signals(void)
{
	signal(SIGINT, &ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
