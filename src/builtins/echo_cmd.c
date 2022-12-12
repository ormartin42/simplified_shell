/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:53:13 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:53:19 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_opt(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	if (str[++i] != 'n')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

int	echo_cmd(int len, char **args)
{
	int	i;
	int	opt;

	opt = is_valid_opt(args[1]);
	i = 1;
	if (opt)
		i++;
	if (i < len)
	{
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (i + 1 < len)
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (!opt)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}
