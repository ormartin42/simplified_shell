/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:02:18 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/16 05:59:34 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_exit_status(int ret)
{
	char	*exitstatus;

	exitstatus = ft_itoa(ret);
	edit_var(&g_g.exitstatus, "?", exitstatus);
	free(exitstatus);
	g_g.hd_sign = 0;
}

static int	exec_fork_handler(t_list *cmds, t_list **env)
{
	int	ret;

	ret = 0;
	if (g_g.hd_sign == 0)
	{
		set_exit_status(0);
		ret = exec_forked_commands(cmds, env);
		g_g.fork = 0;
		set_exit_status(ret);
	}
	return (ret);
}

int	exec_handler(t_list *cmds, t_list **env)
{
	int		ret;
	t_token	*token;
	t_cmd	*cmd;

	ret = 0;
	g_g.fork = 0;
	token = g_g.start;
	if (!token || !ft_strcmp(token->value, ":"))
		return (EXIT_SUCCESS);
	cmd = cmds->data;
	if (ft_lstsize(cmds) == 1 && check_builtin(cmd->name) == TRUE)
	{
		ret = exec_builtin(cmd->name, cmd->args_list, cmd, env);
		set_exit_status(ret);
	}	
	else
		ret = exec_fork_handler(cmds, env);
	return (ret);
}
