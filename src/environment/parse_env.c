/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:01:11 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:01:13 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**	Recupere toutes les variables d'environement stockees dans envp
**	(int main(int argc, char **argc, char **envp)) et les stocke dans
**	une liste chainee composee de structures t_var. Les struc t_var
**	scindent les char* d'envp en 2: une KEY (tout ce qu'il y a avant
**	le '=') et une VALUE (tout ce qu'il y a apres le '=') pour faciliter
**	la recherche/edition des variables par la suite.
*/

int	parse_env(char **envp, t_list **env)
{
	t_var	*var;
	t_list	*new;

	*env = NULL;
	while (*envp)
	{
		if (!ft_strncmp(*envp, "OLDPWD=", 7))
		{
			envp++;
			continue ;
		}
		var = create_var(*envp);
		if (var)
			new = ft_lstnew(var);
		if (!var || !new)
		{
			ft_lstclear(env, free_var);
			if (var)
				ft_putstr_fd("minishell: Problem parsing env\n", 2);
			return (EXIT_FAILURE);
		}
		ft_lstadd_back(env, new);
		envp++;
	}
	return (EXIT_SUCCESS);
}
