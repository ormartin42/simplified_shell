/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:30:46 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/08 15:25:06 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_MERGE_LTOK + FT_MERGE_LTOKEN : regroupe les tokens contenant des lettres
** successifs
** INPUT : "t_token *start" : liste de tokens contenant 1 char a chaque fois
** 1 : regarde combien de tokens type alphanum se suivent
** 2 : les regroupe en un seul token type alphanum
** 3 : supprime elements devenus inutiles
** 4 : re-linke la chaine correctement
** OUTPUT : "t_token *start" : liste token avec type alphanums merge en char *
*/

static void	ft_merge_ltoken(t_token *go, int i)
{
	t_token	*start;
	t_token	*tmp;
	char	*value;

	start = g_g.start;
	while (start && start != go)
		start = start->next;
	while ((i--) > 0)
	{
		value = NULL;
		tmp = start->next;
		value = ft_strjoin(start->value, start->next->value);
		if (!value)
			g_g.error = ft_error("MEMORY ALLOCATION FAILED", NULL, 0, 0);
		free(start->value);
		start->value = value;
		if (start->next->next)
		{
			start->next = start->next->next;
			start->next->prev = start;
		}
		else
			start->next = NULL;
		ft_free_tok(tmp);
	}
}

static void	ft_merge_ltok(void)
{
	int		i;
	t_token	*start;
	t_token	*tmp;

	i = 0;
	start = g_g.start;
	while (start)
	{
		if (!ft_strcmp(start->type, "alphanum"))
		{
			tmp = start;
			start = start->next;
			while (start && !ft_strcmp(start->type, "alphanum"))
			{
				i++;
				start = start->next;
			}
			ft_merge_ltoken(tmp, i);
		}
		else
			start = start->next;
	}
}

/*
** FT_MERGE_REDIR : viens merge les > ou < successifs en << ou >>
** INPUT : "t_token *start" : liste de tokens avec alphanums deja merge
** 1 : cherche deux > ou < successifs
** 2 : les fusionne en un token
** 3 : leur attribue un noucveau type "doubke redir" + sens
** 4 : supprime l'element inutile et relinke la chaine correctement
** OUTPUT : "t_token *start" : list de token avec alpha et redir merge 
*/

static void	ft_merge_redir2(t_token *start, char *flag2)
{
	char	*s;

	s = "simple_redir";
	*flag2 = '\0';
	if (!ft_strncmp(start->type, s, ft_strlen(s))
		&& !ft_strncmp(start->type, start->next->type, ft_strlen(s) + 2))
	{
		*flag2 = start->type[ft_strlen(s) + 1];
		free(start->type);
		free(start->value);
		if (*flag2 == 'r')
		{
			start->type = ft_strdup("double_redir_right");
			start->value = ft_strdup(">>");
		}
		else if (*flag2 == 'l')
		{
			start->type = ft_strdup("double_redir_left");
			start->value = ft_strdup("<<");
		}
	}
}

static void	ft_merge_redir(void)
{
	t_token	*start;
	t_token	*tmp;
	char	flag2;

	start = g_g.start;
	while (start && start->next)
	{
		tmp = NULL;
		ft_merge_redir2(start, &flag2);
		if (flag2)
		{
			tmp = start->next;
			if (start->next->next)
			{
				start->next = start->next->next;
				start->next->next->prev = start;
			}
			else
				start->next = NULL;
			ft_free_tok(tmp);
		}
		start = start->next;
	}
}

/*
** FT_TOKEN : cree des tokens pour chaques buf[2]
** INPUT : char buf[2] : correspondant a 1 char de l'input
** 1 : duplique le content de buf
** 2 : cree un token et lui attribue un type (alphanum/space/redir/pipe)
**     avec ft_create_token
** 3 : l'ajoute a la fin de la liste
** 4 : merge les token "alphanum" successifs avec ft_merge_ltok
** 5 : merge les redirectoins succesives avec ft_merge_redir
** OUTPUT : "t_token *start" : liste contenant des mots, redir, pipes ou espaces
** FCT HORS.c : ft_create_token & ft_get_lasttok -> token/tokenutils.c
*/

void	ft_token(char *buf)
{
	char			*content;
	t_token			*tok;
	t_token			*end;

	content = ft_strdup(buf);
	if (content == NULL)
		g_g.error = ft_error("Memory allocation failed", NULL, 0, 0);
	tok = ft_create_token(content);
	end = ft_get_lasttok();
	if (!end)
		g_g.start = tok;
	else
	{
		end->next = tok;
		tok->prev = end;
	}
	ft_merge_ltok();
	ft_merge_redir();
}
