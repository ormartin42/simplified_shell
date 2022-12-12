/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:50:47 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:50:49 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_heredoc_loop(char *delim, int flag, int fd)
{
	char	*line;
	int		i;

	i = 0;
	ft_init_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (line)
			i = ft_strncmp(line, delim, ft_strlen(delim) + 1);
		if (i == 0)
			break ;
		if (line)
		{
			if (flag)
				line = ft_expendline(line);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free_if(line);
		}
		else
			break ;
	}
	close(fd);
	exit (0);
}

static int	ft_heredoc_handler(char *delim, int flag, int fd)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	pid = fork();
	g_g.hd_sign = 0;
	if (pid == -1)
	{
		ft_putstr_fd("minishell: error creating fork\n", 2);
		return (EXIT_FAILURE);
	}
	g_g.fork = 1;
	if (pid == 0)
		ft_heredoc_loop(delim, flag, fd);
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		if (ret == 1)
			g_g.hd_sign++ ;
		free_if(delim);
	}
	return (ret);
}

static int	ft_heredoc2(t_token *start)
{
	int		file;
	int		ret;
	int		flag;
	char	*name;

	file = ft_double_redir_left(&name);
	if (file == -1)
		return (EXIT_FAILURE);
	free_if(start->value);
	start->value = name;
	ret = ft_heredoc_handler(ft_get_delim(start, &flag), flag, file);
	close(file);
	if (g_g.hd_sign)
	{
		file = open(name, O_TRUNC);
		unlink(name);
		close(file);
	}
	return (ret);
}

void	ft_heredoc(void)
{
	t_token	*start;
	int		ret;
	char	*exitstatus;

	start = g_g.start;
	while (start)
	{
		if (ft_istype(start, "double_redir_left") && !g_g.hd_sign)
		{
			ret = ft_heredoc2(start);
			exitstatus = ft_itoa(ret);
			edit_var(&g_g.exitstatus, "?", exitstatus);
			free_if(exitstatus);
		}
		start = start->next;
	}
}
