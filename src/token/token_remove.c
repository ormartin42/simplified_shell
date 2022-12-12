/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freetok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:24:42 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/08 15:52:59 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_MEMDEL : fct de la libft 
*/

void	ft_memdel(void **truc)
{
	if (truc && *truc)
	{
		free(*truc);
		*truc = 0;
	}
}

/*
** FT_FREE_TOK : free le token passe en parametre
** INPUT : t_token *tok : pointeur sur le token a supprimer
** 1 : verifie l'existence du token
** 2 : re-linke la chaine correctement
** 3 : free le content du token
** 4 : free le token
** OUTPUT : NADA
*/

void	ft_free_tok(t_token	*tok)
{
	if (!g_g.len || !tok)
		return ;
	if (tok->value)
		ft_memdel(&tok->value);
	if (tok->type)
		free(tok->type);
	tok->next = NULL;
	tok->prev = NULL;
	free(tok);
	g_g.len--;
}

/*
** FT_FREE_TOKLIST
** INPUT : "t_token *start" : liste de token issu de la variable globale
** 1 : verifie existence d'au moins un token dans la liste
** 2 : avance dans la liste et free les tokens avec ft_free_tok
** OUTPUT : nothing 
*/

void	ft_free_toklist(void)
{
	t_token	*tmp;
	t_token	*tmp2;

	tmp = g_g.start;
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_free_tok(tmp);
		tmp = tmp2;
	}
}
