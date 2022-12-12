/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:02:51 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:03:01 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_exit_status(int status)
{
	int	ret;

	ret = 0;
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		ret = WTERMSIG(status) + 128;
		if (ret == 130)
			ft_putstr("\n");
		if (ret == 131)
			ft_putstr("Quit: 3\n");
	}
	return (ret);
}

static int	wait_children(int count, pid_t last_pid)
{
	int		ret;
	int		status;
	pid_t	wait_pid;

	while (count)
	{
		wait_pid = wait(&status);
		if (wait_pid == last_pid)
			ret = get_exit_status(status);
		count--;
	}
	return (ret);
}

static int	init_exec_struct(t_list *cmds, t_exec *exec)
{
	exec->count = 0;
	exec->nbr_cmds = ft_lstsize(cmds);
	exec->pipes = open_pipes(exec->nbr_cmds);
	if (!exec->pipes)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	exec_forked_commands(t_list *cmds, t_list **env)
{
	pid_t	pid;
	t_exec	exec;

	if (init_exec_struct(cmds, &exec) == FALSE)
		return (EXIT_FAILURE);
	while (cmds)
	{
		exec.cmd = (t_cmd *)cmds->data;
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd("minishell: error creating fork\n", 2);
			break ;
		}
		g_g.fork = 1;
		if (pid == 0)
		{
			signal(SIGQUIT, handle_signal);
			return (child_process(exec, env));
		}
		exec.count++;
		cmds = cmds->next;
	}
	close_pipes(exec.pipes, exec.nbr_cmds);
	return (wait_children(exec.count, pid));
}
