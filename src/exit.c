/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:05:26 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:05:28 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_msg_handler(void)
{
	if (!g_g.fork)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

void	free_and_restart(void)
{
	if (g_g.error)
	{
		ft_upexitstat(g_g.error);
		g_g.error = 0;
		ft_cl_clear();
		ft_free_toklist();
	}
	else
	{
		ft_free_toklist();
		ft_cl_clear();
	}
}

int	free_all_and_exit(void)
{
	int	ret;

	ret = ft_atoi(search_var(g_g.exitstatus, "?"));
	free_if(g_g.inpt);
	if (g_g.env)
		ft_lstclear(&g_g.env, free_var);
	if (g_g.exitstatus)
		ft_lstclear(&g_g.exitstatus, free_var);
	rl_clear_history();
	return (ret);
}
