/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:53:52 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:53:55 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	display_error_msg(char **arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

int	exit_cmd(int argc, char **arg)
{
	int	i;

	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 1);
	if (argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (argc == 2)
	{
		if ((arg[1][0] == '+' || arg[1][0] == '-') && !arg[1][1])
			return (display_error_msg(arg));
		i = -1;
		while (arg[1][++i])
		{
			if (!ft_isdigit(arg[1][i]))
				return (display_error_msg(arg));
		}
		return (ft_atoi(arg[1]));
	}
	return (EXIT_SUCCESS);
}
