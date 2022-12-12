/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:04:02 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:04:04 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	reinit_redirections(int fd[2])
{
	if (fd[0] >= 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] >= 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}

static int	dup_fds(t_redir redir)
{
	int	file;
	int	ret;

	file = create_file(redir.type, redir.file);
	if (file == -1)
		return (EXIT_FAILURE);
	if (redir.type == 1 || redir.type == 2)
		ret = dup2(file, STDOUT_FILENO);
	else
		ret = dup2(file, STDIN_FILENO);
	if (ret < 0)
		printf("error duping\n");
	ret = close(file);
	if (ret == -1)
		printf("error closing\n");
	return (EXIT_SUCCESS);
}

static int	backup_fds(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
	fd[0] = dup(STDIN_FILENO);
	if (fd[0] < 0)
	{
		ft_putstr_fd("Minishell: STDIN save fail\n", 2);
		return (EXIT_FAILURE);
	}
	fd[1] = dup(STDOUT_FILENO);
	if (fd[1] < 0)
	{
		ft_putstr_fd("Minishell: STDOUT save fail\n", 2);
		close(fd[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	handle_redirections(t_cmd *cmd, int fd[2])
{
	t_list	*redir_list;
	t_redir	*redir;

	if (backup_fds(fd) == 1)
		return (EXIT_FAILURE);
	redir_list = cmd->redir_list;
	while (redir_list)
	{
		redir = redir_list->data;
		if (dup_fds(*redir))
			return (EXIT_FAILURE);
		redir_list = redir_list->next;
	}
	return (EXIT_SUCCESS);
}
