/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:31:12 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/08 15:31:00 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_GET_LASTTOK : Renvoie le dernier token de la liste
** INPUT : "t_token *start" : liste de tokens
** 1 : avance jusqu'au dernier token
** OUTPUT : t_token *start : pointeur sur dernier token de la liste 
*/

t_token	*ft_get_lasttok(void)
{
	t_token	*start;

	start = g_g.start;
	while (start && start->next)
		start = start->next;
	return (start);
}

/*
** FT_CREATE_TOKEN : Cree un token contenant le content passse en input
** INPUT : void *content : ce sera en fait un char * = contenu du token
** 1 : transforme le void * en char * 
** 2 : duplique le type obtenu avec ft_token_type
** 3 : fait pointer la value du token vers content et type vers type
** 4 : fait pointer le pointeur sur next et prev vers NULL
** OUTPUT : t_token *tok : token fraichement cree non linke
*/

t_token	*ft_create_token(void *content)
{
	t_token	*tok;
	char	*type;
	char	*c;

	tok = NULL;
	type = NULL;
	c = (char *)(content);
	tok = malloc(sizeof(t_token));
	type = ft_strdup(ft_token_type(c[0]));
	if (tok == NULL || type == NULL)
		ft_error("Memory allocation failed", NULL, 0, 0);
	tok->value = content;
	tok->type = type;
	tok->prev = NULL;
	tok->next = NULL;
	g_g.len++;
	return (tok);
}

/*
** FT_REMOVE_TOKEN : free et retire le token de la liste
** INPUT : t_token *del : pointeur sur le token a remove
** 1 : avance dans la liste jusqu'a tomber sur le token a delete
** 2 : relinke la liste pour exclure le token souhaite
** 3 : free le token et son contenu
** OUTPUT : rien
** FCT HORS .C : ft_free_tok -> error/freetok.c
*/
void	ft_remove_token(t_token *del)
{
	t_token	*start;

	start = g_g.start;
	while (start && start != del)
		start = start->next;
	if (start)
	{
		if (start->prev && start->next)
		{
			start->prev->next = start->next;
			start->next->prev = start->prev;
		}
		else if (start->prev && !start->next)
			start->prev->next = NULL;
		else if (start->next && !start->prev)
		{
			start->next->prev = NULL;
			g_g.start = start->next;
		}
		else if (!start->prev && !start->next)
			g_g.start = NULL;
		ft_free_tok(start);
	}
}

/*
** FCT_REMOVE_SPACE : remove les tokens space et compte le nombre de pipe
** INPUT : "t_token *start" : issue de g.start
** 1 : avance dans la liste et remove les tokens space
** OUTPUT : "t_token *start" sans les espaces
** FCT HORS .c : ft_istype -> token/token_type_value,
**               ft_remove_token -> error/freetok.c
*/

void	ft_remove_space(void)
{
	t_token	*tok;
	t_token	*tmp;

	tok = g_g.start;
	while (tok)
	{
		if (ft_istype(tok, "space"))
		{
			tmp = tok;
			tok = tok->next;
			ft_remove_token(tmp);
		}
		else
			tok = tok->next;
	}
}

/*
** FT_TOKEN_TYPE : renvoie le type dont sera le token contenant le char d'input
** INPUT : char c : char contenant dans buf[0] 
** 1 : Foret d'if pour retrouver le type correspondant
** OUTPUT : char *type : type du token qui va etre cree
*/

char	*ft_token_type(char c)
{
	if (c == '|')
		return ("pipeline");
	else if (c == '<')
		return ("simple_redir_left");
	else if (c == '>')
		return ("simple_redir_right");
	else if (c == '\"')
		return ("double_quote");
	else if (c == '\'')
		return ("single_quote");
	else if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return ("space");
	else if (c == ' ')
		return ("space");
	else if (c == '$')
		return ("variable");
	else if (c == 0)
		return (0);
	else
		return ("alphanum");
}
