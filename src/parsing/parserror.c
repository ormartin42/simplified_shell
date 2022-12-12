/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:30:49 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 13:59:26 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_err2(t_token *tok)
{
	tok = tok->next;
	while (tok)
	{
		if (ft_isredir(tok, 1))
		{
			g_g.error = ft_errormod("Syntax error near unexpected token `",
					(char *)tok->value, 1, 258);
			return ;
		}
		else if (ft_istype(tok, "space"))
			tok = tok->next;
		else
			return ;
	}
}

static void	ft_err1(t_token *tok)
{
	tok = tok->next;
	while (tok)
	{
		if (ft_isredir(tok, 1))
		{
			g_g.error = ft_errormod("Syntax error near unexpected token `",
					"|", 1, 258);
			return ;
		}
		else if (ft_istype(tok, "space"))
			tok = tok->next;
		else
			return ;
	}
}

static void	ft_err0(void)
{
	t_token	*tok;

	tok = g_g.start;
	while (tok)
	{
		if (ft_istype(tok, "pipeline"))
		{
			ft_err1(tok);
			if (g_g.error)
				return ;
		}
		else if (ft_isredir(tok, 0))
		{
			ft_err2(tok);
			if (g_g.error)
				return ;
		}
		tok = tok->next;
	}
}

void	ft_synerror(void)
{
	t_token	*tok;
	t_token	*tmp;

	tmp = NULL;
	tok = g_g.start;
	while (tok)
	{
		if (!ft_istype(tok, "space"))
			tmp = tok;
		tok = tok->next;
	}
	ft_err0();
	if (g_g.error)
		return ;
	if (tmp && ft_isredir(tmp, 1))
		g_g.error = ft_errormod("Syntax error near unexpected token `newline",
				NULL, 1, 258);
}
