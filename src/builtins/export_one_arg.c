/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_one_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:54:04 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:54:15 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_env(t_var **tab)
{
	while (*tab)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((*tab)->key, STDOUT_FILENO);
		if ((*tab)->value)
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			ft_putstr_fd((*tab)->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tab++;
	}
}

static void	sort_env(t_var **tab)
{
	int		i;
	int		j;
	t_var	*tmp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i]->key, tab[j]->key) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	print_sorted_env(t_list *env)
{
	t_var	**tab;
	t_var	*var;
	int		i;

	tab = (t_var **)ft_calloc(ft_lstsize(env), sizeof(t_var *));
	if (!tab)
	{
		ft_putstr_fd("minishell: export: Malloc error\n", 2);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (env)
	{
		var = (t_var *)env->data;
		env = env->next;
		if (!ft_strcmp(var->key, "?") || !ft_strcmp(var->key, "_"))
			continue ;
		tab[i++] = var;
	}
	sort_env(tab);
	print_env(tab);
	free_if(tab);
	return (EXIT_SUCCESS);
}
