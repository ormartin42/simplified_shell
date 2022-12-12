/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:03:38 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/16 06:03:54 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	simple_redir_right(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: error opening file (\">\")\n", 2);
		return (fd);
	}
	return (fd);
}

static int	double_redir_right(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{	
		ft_putstr_fd("minishell: error opening file (\">>\")\n", 2);
		return (fd);
	}
	return (fd);
}

static int	simple_redir_left(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		edit_var(&g_g.exitstatus, "?", "1");
		return (fd);
	}
	return (fd);
}

static int	double_redir_left(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		edit_var(&g_g.exitstatus, "?", "1");
		return (fd);
	}
	unlink(filename);
	return (fd);
}

int	create_file(int type, char *filename)
{
	int	fd;

	if (check_permissions(filename) == 1)
		return (-1);
	if (type == 1)
		fd = simple_redir_right(filename);
	else if (type == 2)
		fd = double_redir_right(filename);
	else if (type == 3)
		fd = simple_redir_left(filename);
	else
		fd = double_redir_left(filename);
	return (fd);
}
