/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:02:07 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:02:09 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_command_error(char *cmd)
{
	g_g.signal = 1;
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static int	exec_command(t_cmd *cmd, char **args, t_list **env)
{
	int		ret;
	char	*abs_path;

	ret = 0;
	if (!cmd->name)
		return (ret);
	else if (check_builtin(cmd->name) == TRUE)
		return (exec_builtin(cmd->name, cmd->args_list, cmd, env));
	else
	{
		ret = get_absolute_path(&abs_path, args, *env);
		if (ret == 0)
		{
			ret = execve(abs_path, args, list_to_tab(*env));
			perror("minishell: execve");
			return (ret);
		}
		else if (ret == 1)
		{	
			print_command_error(cmd->name);
			return (127);
		}
	}
	return (ret);
}

int	child_process(t_exec exec, t_list **env)
{
	int		ret;
	char	**args;

	handle_fds(exec.pipes, exec.count, exec.nbr_cmds, exec.cmd);
	args = args_list_to_tab(exec.cmd->args_list);
	ret = exec_command(exec.cmd, args, env);
	reinit_redirections(exec.cmd->fd);
	free_array(args);
	exit (ret);
}
