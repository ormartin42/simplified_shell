/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:03:29 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:03:31 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	close_fds(int count, int nbr_pipes, t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < (count - 1))
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	if (count != 0)
		close(pipes[i++][1]);
	if (i < nbr_pipes)
		close(pipes[i++][0]);
	while (i < nbr_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	dup_fds(int count, int nbr_pipes, t_pipes *pipes)
{
	if (count != 0)
	{
		if (dup2(pipes[count - 1][0], STDIN_FILENO) == -1)
		{
			close(pipes[count - 1][0]);
			if (count < nbr_pipes)
				close(pipes[count][1]);
			ft_putstr_fd("minishell: error duping stdin\n", 2);
			return (EXIT_FAILURE);
		}
		close(pipes[count - 1][0]);
	}
	if (count < nbr_pipes)
	{
		if (dup2(pipes[count][1], STDOUT_FILENO) == -1)
		{
			close(pipes[count][1]);
			ft_putstr_fd("minishell: error duping stdout\n", 2);
			return (EXIT_FAILURE);
		}
		close(pipes[count][1]);
	}
	return (EXIT_SUCCESS);
}

void	handle_fds(t_pipes *pipes, int count, int nbr_cmds, t_cmd *cmd)
{
	int	ret;
	int	nbr_pipes;

	nbr_pipes = nbr_cmds - 1;
	ret = close_fds(count, nbr_pipes, pipes);
	if (ret == TRUE)
		ret = dup_fds(count, nbr_pipes, pipes);
	if (ret == TRUE)
		ret = handle_redirections(cmd, cmd->fd);
	if (ret == FALSE)
		exit (ret);
}
