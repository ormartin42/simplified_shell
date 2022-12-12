/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:01:21 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:01:23 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**	Pour free une struct de type t_var. Param void * car necessaire pour lstclear
*/

void	free_var(void *var)
{
	t_var	*tmp;

	tmp = (t_var *)var;
	free_if(tmp->key);
	free_if(tmp->value);
	free_if(tmp);
}

/*
**	Cherche dans la liste chainee de variables d'environement la KEY precise et si
**	elle la trouve, renvoie un pointeur sur le debut de la VALUE de la variable
**	(juste apres le '='). Sinon renvoie NULL.
*/

char	*search_var(t_list *env, char *key)
{
	t_var	*var;

	while (env)
	{
		var = (t_var *)env->data;
		if (!ft_strcmp(var->key, key))
			return (var->value);
		env = env->next;
	}
	return (NULL);
}

/*
**	Transforme la liste chainee ENV en tableau (notamment pour l'envoyer a execve
**	et pour le builtin env)
*/

static void	*free_and_return(char **table, int max)
{
	int		i;

	i = 0;
	while (i < max)
		free_if(table[i++]);
	free(table);
	return (NULL);
}

static char	*data_to_str(t_var var)
{
	char	*env_str;

	env_str = (char *)ft_calloc(ft_strlen(var.key) + ft_strlen(var.value) + 2,
			sizeof(char));
	if (!env_str)
		return (NULL);
	ft_strcat(env_str, var.key);
	ft_strcat(env_str, "=");
	ft_strcat(env_str, var.value);
	return (env_str);
}

char	**list_to_tab(t_list *env)
{
	int		i;
	char	*str;
	char	**envp;
	t_var	var;

	envp = (char **)ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		var = *(t_var *)env->data;
		if (!var.value)
		{
			env = env->next;
			continue ;
		}
		str = data_to_str(var);
		if (!str)
			return (free_and_return(envp, i));
		envp[i++] = str;
		env = env->next;
	}
	envp[i] = 0;
	return (envp);
}
