/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:05:12 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:06:59 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_error(char *msg, char *add, int on, int err)
{
	rl_clear_history();
	ft_putstr_fd("minishell: ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (add)
		ft_putstr_fd(add, 2);
	if (msg)
		ft_putstr_fd("\n", 2);
	if (on)
		return (err);
	return (EXIT_FAILURE);
}

int	ft_errormod(char *msg, char *add, int on, int err)
{
	rl_clear_history();
	ft_putstr_fd("minishell: ", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	if (add)
		ft_putstr_fd(add, 2);
	if (msg)
		ft_putstr_fd("'\n", 2);
	if (on)
		return (err);
	return (1);
}

void	ft_upexitstat(int error)
{
	char	*exitstatus;

	if (error == 0)
		return ;
	exitstatus = ft_itoa(error);
	edit_var(&g_g.exitstatus, "?", exitstatus);
	free(exitstatus);
}
