/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 19:55:22 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/15 06:31:05 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_merge_double2(t_token *start)
{
	if ((ft_istype(start, "alphanum") && ft_istype(start->next, "alphanum")) \
			|| (ft_istype(start, "variable")
			&& ft_istype(start->next, "variable")))
		return (1);
	return (0);
}

void	ft_merge_double(void)
{
	t_token	*start;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		start = g_g.start;
		while (start)
		{
			if (start->next)
			{
				if (ft_merge_double2(start))
				{
					ft_merge_tok(start, 2, 0);
					flag++;
				}
			}
			start = start->next;
		}
	}
}

/*
** FT_MERGE_TOK + FT_MERGE_TOK2 : merge 2 token on choisit le type et value
** INPUT : t_token *tok : premier token de deux token a merge
** INPUT2 : int val : value a utiliser 0 tok->value, 1 next->value, 2 join des 2
** INPUT3 : int type : type a utiliser 0 tok->type, 1 tok->next->type
** 1 : verifie que tok->next existe et les inputs sont bon
** 2 : duplique value et type choisis
** 3 : free tok->value & tok->type et leur attribue les type et value choisis
** 4 : (mergetok2) relink correctement et free tok->next
** OUTPUT : RI1
*/

static void	ft_merge_tok2(t_token *tok, t_token *tmp)
{
	if (tmp->next)
	{
		tok->next = tmp->next;
		tmp->next->prev = tok;
	}
	else
		tok->next = NULL;
	ft_free_tok(tmp);
}

void	ft_merge_tok(t_token *tok, int val, int type)
{
	t_token	*tmp;
	char	*value;
	char	*stype;

	tmp = tok->next;
	if (!tmp || val < 0 || val > 2 || type < 0 || type > 1)
		return ;
	if (val == 2)
		value = ft_strjoin(tok->value, tmp->value);
	else if (val == 0)
		value = ft_strdup(tok->value);
	else
		value = ft_strdup(tmp->value);
	if (type == 0)
		stype = ft_strdup(tok->type);
	else
		stype = ft_strdup(tmp->type);
	free(tok->type);
	free(tok->value);
	tok->type = stype;
	tok->value = value;
	ft_merge_tok2(tok, tmp);
}

/*
** FT_MERGE_ALPHA_VAR : si token alphanum suivi de variable ->merge
** INPUT : "t_token *start" : liste de token stockee dans la globale
** 1 : avance jusqu'a trouver un token alphanum suivi d' un variable
** 2 : les merge
** 3 : si ke token est type spe le remplace par un alphanum = a g.error
** OUTPUT : "t_token *start" : avec variable=Yesai merge sous un token
*/

void	ft_merge_alpha_var(void)
{
	t_token	*start;

	start = g_g.start;
	while (start)
	{
		if (ft_istype(start, "alphanum"))
		{
			if (start->next && ft_istype(start->next, "variable"))
				ft_merge_tok(start, 2, 0);
		}
		else if (ft_istype(start, "spe"))
		{
			ft_change_type(start, "alphanum");
			ft_upexitstat(g_g.error);
			ft_change_value(start, search_var(g_g.exitstatus, "?"));
		}
		start = start->next;
	}
}
