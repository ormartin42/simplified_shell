/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:30:40 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/08 15:31:32 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_CHANGE_VALUE : modifie la value du token passe en parametre
** INPUT : t_token *tok : pointeur sur token dont la value doit etre modifiee
** INPUT2 : char *value : nouvelle value a attribuer
** 1 : free ancienne value
** 2 : duplique nouvelle value avec strdup 
** 3 : fait pointer le pointeur value du token vers la nouvelle value dupliquee
** 4 : verifie que le malloc de strdup n ai pas fail 
 ** OUTPUT : rien
*/

void	ft_change_value(t_token *tok, char *value)
{
	if (tok && tok->value)
	{
		if (tok->value)
			free(tok->value);
		tok->value = ft_strdup(value);
		if (!tok->value)
			g_g.error = ft_error("Memory allocation failed", NULL, 0, 0);
	}
}

/*
** FT_CHANGE_TYPE : modifie le type du token passe en parametre
** INPUT : t_token *tok : pointeur sur token dont le type doit etre modifie
** INPUT2 : char *type : nouveau type a attribuer
** 1 : free ancien type
** 2 : duplique nouveau type avec strdup 
** 3 : fait pointer le pointeur type du token vers le nouveau type duplique
** 4 : verifie que le malloc de strdup n ai pas fail 
** OUTPUT : rien
*/

void	ft_change_type(t_token *tok, char *type)
{
	if (tok->type)
		free(tok->type);
	tok->type = ft_strdup(type);
	if (!tok->type)
		g_g.error = ft_error("Memory allocation failed", NULL, 0, 0);
}

/*
** FT_ISTYPE : verifie le type du token passe en parametre
** INPUT : t_token *tok : pointeur sur token dont le type doit etre verifie
** INPUT2 : char *type : type a tester
** 1 : strcmp entre le type du token et le type du parametre 
** OUTPUT : BOOLEAN 1 si meme type / 0 sinon 
*/

int	ft_istype(t_token *tok, char *type)
{
	if (!ft_strcmp(tok->type, type))
		return (1);
	else
		return (0);
}

/*
** FT_ISREDIR : verifie si le token passe en parametre est une redirection
** INPUT : t_token *tok : pointeur sur token dont le type doit etre verifie
** INPUT2 : int 1:on / 0:off : flag pour inclure ou non le pipe comme une redir
** 1 : suite de ft_istype avec tout les types de redirections
** OUTPUT : BOOLEAN 1 si redir / 0 sinon
*/

int	ft_isredir(t_token *tok, int pipe)
{
	if (ft_istype(tok, "simple_redir_right")
		|| ft_istype(tok, "simple_redir_left")
		|| ft_istype(tok, "double_redir_left")
		|| ft_istype(tok, "double_redir_right"))
		return (1);
	if (pipe)
		if (ft_istype(tok, "pipeline"))
			return (1);
	return (0);
}

/*
** FT_ISLIT : verifie si le token en parametre est literral = (cmd arg ou rarg)
** INPUT : t_token *tok : pointeur sur token dont le type doit etre verifie
** 1 : suite de ft_istype avec tout les types de litteraux
** OUTPUT : BOOLEAN 1 si litteral / 0 sinon
*/

int	ft_islit(t_token *tok)
{
	if (ft_istype(tok, "cmd") || ft_istype(tok, "arg")
		|| ft_istype(tok, "rarg"))
		return (1);
	return (0);
}
