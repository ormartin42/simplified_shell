/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 14:07:03 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 13:59:56 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_CHECK_QUOTES : va verifier que toutes les quotes sont bien fermees
** INPUT : "t_token *start" : chaine de token de variable globale g.start
** 1 : avance dans la liste et incremente in flag si des quotes sont trouvees
** le flag depend du type de quote et ne prend pas en compte les quote precedees
** par un backslash 
** 2 : decremente le flag si elle sont fermees
** 3 : si le flag est toujours on a la fin affiche un message d'erreur
** OUTPUT : "int g.error" code erreur stocke dans variable globale
*/

static void	ft_check_quotes2(int *open, int flag)
{
	if (!flag)
	{
		if (*open == 0)
			*open = 1;
		else if (*open == 1)
			*open = 0;
	}
	else
	{
		if (*open == 0)
			*open = 2;
		else if (*open == 2)
			*open = 0;
	}
}

void	ft_check_quotes(void)
{
	t_token	*start;
	int		open;

	open = 0;
	start = g_g.start;
	while (start != NULL)
	{
		if ((!start->prev || ft_strcmp((char *)start->prev->type, "backslash"))
			&& !ft_strcmp((char *)start->type, "single_quote"))
			ft_check_quotes2(&open, 0);
		if ((!start->prev || ft_strcmp((char *)start->prev->type, "backslash"))
			&& !ft_strcmp((char *)start->type, "double_quote"))
			ft_check_quotes2(&open, 1);
		start = start->next;
	}
	if (open != 0)
		g_g.error = ft_error("Syntax error unclosed quotes", NULL, 0, 0);
}

/*
** FT_SINGLEQUOTE : remplace le type des token entre single par alphanum
**                  sauf espace
** INPUT : t_token **start : adresse pointeur sur premier token type singlequote
** 1 : remove le token de la quote (ft_remove_token)
** 2 : modifie le type de tout les tokens suivants par alphanum
** 3 : lorsque trouve une autre single la remove et sort de la boucle 
** OUTPUT : "t_token **start" pointeur de pointeur sur token sortie de boucle
** FCT HORS .c : ft_remove_token -> error/freetok.c ,
**               ft_changetype token/token_type_value.c
*/

static void	ft_singlequote(t_token **start)
{
	t_token	*tmp;

	tmp = *start;
	*start = (*start)->next;
	while (ft_strcmp((*start)->type, "single_quote"))
	{
		if (ft_strcmp((*start)->type, "space"))
			ft_change_type(*start, "alphanum");
		*start = (*start)->next;
	}
	tmp = *start;
	*start = (*start)->next;
}

/*
** FT_DOUBLEQUOTE : remplace le type des token entre double par alphanum
**                  sauf espace et variable
** INPUT : t_token **start : adresse pointeur sur premier token type doubleq
** 1 : remove le token de la quote (ft_remove_token)
** 2 : modifie le type de tout les tokens suivants par alphanum
** 3 : lorsque trouve une autre double la remove et sort de la boucle
** OUTPUT : "t_token **start" pointeur de pointeur sur token sortie de boucle
** FCT HORS .c : ft_remove_token -> error/freetok.c ,
**               ft_changetype token/token_type_value.c
*/

static void	ft_doublequote(t_token **start)
{
	t_token	*tmp;

	tmp = *start;
	*start = (*start)->next;
	while (ft_strcmp((*start)->type, "double_quote"))
	{
		if (ft_strcmp((*start)->type, "variable")
			&& ft_strcmp((*start)->type, "space"))
			ft_change_type(*start, "alphanum");
		*start = (*start)->next;
	}
	tmp = *start;
	*start = (*start)->next;
}

/*
** FT_QUOTES : avance dans g.start et appelle les fonctions spe quotes au besoin
** INPUT : "t_token *start" : chaine de token de variable globale g.start
** 1 : avance jusqu'a la premiere single ou double quote
** 2 : appelle la fonction correspondante en envoyant l'adresse du pointeur 
**     afin que l'on garde l'info de l'avancement dans la chaine dans la fct
** OUTPUT : "t_token *start" : chaine de token avec quotes appliquees et suppr
*/

void	ft_quotes(void)
{
	t_token	*start;

	start = g_g.start;
	while (start)
	{
		if (!ft_strcmp(start->type, "single_quote"))
			ft_singlequote(&start);
		else if (!ft_strcmp(start->type, "double_quote"))
			ft_doublequote(&start);
		else
			start = start->next;
	}
}
