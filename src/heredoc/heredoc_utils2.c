/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:51:56 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:52:01 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_delim_quote(t_token *start)
{
	char	*delim;
	char	*qtype;

	qtype = start->type;
	delim = NULL;
	if (start->next && ft_strcmp(start->next->type, qtype))
		start = start->next;
	else
		return (NULL);
	while (start && start->next && ft_strcmp(start->next->type, qtype))
	{
		ft_merge_tok(start, 2, 1);
		ft_change_type(start, "alphanum");
	}
	if (start)
	{
		delim = ft_strdup(start->value);
		ft_remove_token(start);
		return (delim);
	}
	return (NULL);
}

static char	*ft_get_delim2(t_token *start, int num)
{
	char	*delim;

	if (num == 1)
	{
		delim = ft_strdup(start->value);
		ft_remove_token(start);
	}
	else
	{
		ft_merge_tok(start, 2, 1);
		delim = ft_strdup(start->value);
		ft_remove_token(start);
	}
	return (delim);
}

char	*ft_get_delim(t_token *tok, int *flag)
{
	t_token	*start;

	start = tok;
	*flag = 1;
	while (start)
	{
		if (ft_istype(start, "alphanum"))
			return (ft_get_delim2(start, 1));
		else if (ft_istype(start, "variable"))
		{
			if (start->next && ft_istype(start->next, "alphanum"))
				return (ft_get_delim2(start, 2));
		}
		else if (ft_istype(start, "single_quote") \
				|| ft_istype(start, "double_quote"))
		{
			*flag = *flag - 1;
			return (ft_delim_quote(start));
		}
		start = start->next;
	}
	return (NULL);
}
