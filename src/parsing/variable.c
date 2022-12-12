/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 15:14:32 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/14 19:40:58 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_PREP_VARIABLE : regroupe les tokens '$' et leur clefs sous un meme token 
** INPUT : "t_token *start" chaine de token issue de g.start
** 1 : avance dans la chaine jusqu'a tomber sur un token variable == '$'
** 1.a : si le suivant est un alpanum retire le $ t change son type en variable
** 1.b : si le suivant est un "?" retire le $ et change son type en spe
** 1.c : si le suivant n'est ni alphanum ni "?" change le type en alphanum
** OUTPUT : "t_token *start" $ retires et type variable attribue au clefs 
** FCT HORS .c : ft_remove_token -> error/freetok.c ,
**               ft_changetype token/token_type_value.c
*/

static t_token	*ft_prep_variable2(t_token *start, int flag)
{
	t_token	*tmp;

	if (start->next && !ft_strcmp(start->next->value, "'"))
	{
		start = start->next;
		return (start);
	}
	tmp = start;
	start = start->next;
	ft_remove_token(tmp);
	if (!flag)
		ft_change_type(start, "variable");
	else
		ft_change_type(start, "spe");
	start = start->next;
	return (start);
}

void	ft_prep_variable(void)
{
	t_token	*start;

	start = g_g.start;
	while (start && start->type)
	{
		if (!ft_strcmp(start->type, "variable"))
		{
			if (start->next && !ft_strcmp(start->next->type, "alphanum")
				&& ft_strcmp((char *)start->next->value, "?"))
				start = ft_prep_variable2(start, 0);
			else if (start->next
				&& !ft_strcmp((char *)start->next->value, "?"))
				start = ft_prep_variable2(start, 1);
			else if (!ft_strcmp((char *)start->value, "$"))
			{
				ft_change_type(start, "alphanum");
				start = start->next;
			}
			else
				start = start->next;
		}
		else
			start = start->next;
	}
}

/*
** FT_EXPEND_VARIABLE : va remplacer la value des tokens var par vrai valeur
** INPUT : "t_token *start" : chaine de token issue de g.start
** INPUT2 : "t_env *env" : liste des variables d'environnement issue de g.env
** 1 : avance dans la chaine jusqu a trouver un type variable
** 2 : va chercher le key ( =value du token type variable dans env)
** 3 : si key dans var remplace value du token par value de la varibabl dans var
** 4 : si key non retrouvee remove token
** OUTPUT : "t_token *start" : liste avec variables expended
** FCT HORS .c : ft_remove_token -> error/freetok.c ,
**               ft_changetype token/token_type_value.c
*/

static int	ft_expend_variable2(t_token **start)
{
	t_list	*env;
	t_var	*var;
	t_token	*tmp;

	env = g_g.env;
	tmp = *start;
	while (env && env->data)
	{
		var = env->data;
		if (!ft_strcmp((char *)tmp->value, var->key))
		{
			ft_change_value(tmp, var->value);
			break ;
		}
		env = env->next;
	}
	*start = (*start)->next;
	if (!env)
		ft_remove_token(tmp);
	return (0);
}

void	ft_expend_variable(void)
{
	t_token	*start;
	char	**tab;

	start = g_g.start;
	while (start)
	{
		if (!ft_strcmp(start->type, "variable"))
		{
			tab = ft_splitmod(start);
			if (tab != NULL)
				ft_expend_variable3(&start, tab);
			else
				ft_expend_variable2(&start);
		}
		else
			start = start->next;
	}
}
