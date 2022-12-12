/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:53:36 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:53:43 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_cmd(t_list *env)
{
	int		i;
	char	**envp;

	envp = list_to_tab(env);
	if (!envp)
	{
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	free_array(envp);
	return (EXIT_SUCCESS);
}
