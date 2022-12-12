/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:54:29 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:54:31 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** PWD permet d'afficher le repertoire courrant
*/

int	pwd_cmd(void)
{
	char	pwd[PATH_MAX + 1];

	if (!getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd("minishell: pwd: getcwd error\n", 2);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', 1);
	return (EXIT_SUCCESS);
}
