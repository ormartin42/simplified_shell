/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:00:42 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:00:45 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**	"Append" une valeur a la suite d'une variable d'environement existante.
**	Utilise surtout pour le builtin export, qui en fonction de la presence
**	ou non de double quotes dans la declaration de la variable, peut necessiter
**	append des valeurs apres au lieu de cree/remplacer. Ex : pour une variable
**	qui existe deja (A=3) : export A=$A"hello" donnera A=3hello. 
**	Sans les double quotes : A=$Ahello donnera A=
*/

int	append_var(t_list **env, char *key, char *app)
{
	char	*dest;
	char	*var;
	char	len;

	len = 0;
	var = search_var(*env, key);
	if (var)
		len = ft_strlen(var);
	dest = (char *)ft_calloc(len + ft_strlen(app) + 1, sizeof(char));
	if (!dest)
	{
		ft_putstr_fd("minishell: append_var: Malloc error\n", 2);
		return (EXIT_FAILURE);
	}
	if (var)
		ft_strcat(dest, var);
	ft_strcat(dest, app);
	edit_var(env, key, dest);
	free_if(dest);
	return (0);
}

/*
**	EDIT_VAR va dabord checker si la KEY donnee en parametre correspond a la
**	KEY d'une variable existante. Si oui, elle va remplacer la value de la 
**	variable par la VALUE donee en parametre. Si aucune key ne correspond,
**	on va continuer dans EDIT_VAR2 qui va creer une nouvelle variable et la
**	rajouter a la finde la liste chainee env.
*/

static int	add_var(t_list **env, char *key, char *value)
{
	t_var	*var;
	t_list	*new;

	var = (t_var *)ft_calloc(1, sizeof(t_var));
	if (!var)
	{
		ft_putstr_fd("minishell: create_var: Malloc error\n", 2);
		return (EXIT_FAILURE);
	}
	var->key = ft_strdup(key);
	if (var->key && value)
		var->value = ft_strdup(value);
	if (!var->key || (value && !var->value))
	{
		ft_putstr_fd("minishell: create_var: Problem creating new var\n", 2);
		return (EXIT_FAILURE);
	}
	new = ft_lstnew(var);
	if (!new)
	{
		ft_putstr_fd("minishell: create_var: Problem creating new var\n", 2);
		return (EXIT_FAILURE);
	}
	ft_lstadd_back(env, new);
	return (EXIT_SUCCESS);
}

int	edit_var(t_list **env, char *key, char *value)
{
	t_var	*var;
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		var = (t_var *)tmp->data;
		if (!ft_strcmp(var->key, key))
		{
			if (value)
			{
				free(var->value);
				var->value = ft_strdup(value);
				if (!var->value)
				{
					ft_putstr_fd("minishell: problem editing var\n", 2);
					return (EXIT_FAILURE);
				}
			}
			return (EXIT_SUCCESS);
		}
		tmp = tmp->next;
	}
	return (add_var(env, key, value));
}

/*
**	CREATE_VAR cree un nouvel element t_var et le renvoie
*/

t_var	*create_var(char *str)
{
	int		i;
	t_var	*var;

	var = (t_var *)ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->key = ft_substr(str, 0, i);
	if (!var->key)
	{
		ft_putstr_fd("minishell: problem creating var key\n", 2);
		return (NULL);
	}
	str += i + 1;
	var->value = ft_strdup(str);
	if (!var->value)
	{
		ft_putstr_fd("minishell: problem creating var value\n", 2);
		return (NULL);
	}
	return (var);
}
