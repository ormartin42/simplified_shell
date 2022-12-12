/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:54:42 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:56:53 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	compare_var(t_var *var, t_var *ref)
{
	return (ft_strcmp(var->key, ref->key));
}

static void	remove_var(t_list **lst, void *data)
{
	t_list	*curr;
	t_list	*tmp_prev;

	curr = *lst;
	tmp_prev = NULL;
	while (curr)
	{
		if (compare_var(curr->data, data) == 0)
		{
			free_var(curr->data);
			if (!tmp_prev)
				*lst = curr->next;
			else
				tmp_prev->next = curr->next;
			free_if(curr);
			return ;
		}
		tmp_prev = curr;
		curr = curr->next;
	}
}

int	unset_cmd(int len, char **args, t_list **env)
{
	int		i;
	t_var	var;

	if (len == 1)
		return (EXIT_SUCCESS);
	i = 0;
	while (i < len)
	{
		var.key = args[i++];
		remove_var(env, &var);
	}
	return (EXIT_SUCCESS);
}
