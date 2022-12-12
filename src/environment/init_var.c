/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:00:53 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:01:43 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_var(void)
{
	char	pwd[PATH_MAX + 1];
	char	*shlvl;

	if (!search_var(g_g.env, "PWD"))
		edit_var(&g_g.env, "PWD", getcwd(pwd, sizeof(pwd)));
	shlvl = NULL;
	if (!search_var(g_g.env, "SHLVL"))
		edit_var(&g_g.env, "SHLVL", "1");
	else
	{
		shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
		edit_var(&g_g.env, "SHLVL", shlvl);
		free(shlvl);
	}
	edit_var(&g_g.exitstatus, "?", "0");
}
