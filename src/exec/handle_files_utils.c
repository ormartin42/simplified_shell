/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_files_utils.c	                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:03:38 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/15 03:38:59 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_permissions(char *filename)
{
	DIR	*dir;

	dir = opendir(filename);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		edit_var(&g_g.env, "?", "1");
		return (EXIT_FAILURE);
	}
	else if (access(filename, F_OK) == 0)
	{
		if (access(filename, R_OK | W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			edit_var(&g_g.env, "?", "1");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
