/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:20:12 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:04:47 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_check_heredoc(t_list *redlist)
{
	t_redir	*red;

	while (redlist)
	{
		red = redlist->data;
		if (red->type == 4)
			return (1);
		redlist = redlist->next;
	}
	return (0);
}

void	ft_gib_order(void)
{
	t_list	*list;
	t_cmd	*cmd;
	t_list	*redlist;
	int		i;

	i = 1;
	list = g_g.cl;
	while (list)
	{
		cmd = list->data;
		redlist = cmd->redir_list;
		if (ft_check_heredoc(redlist))
			cmd->i = i++;
		list = list->next;
	}
	list = g_g.cl;
	while (list)
	{
		cmd = list->data;
		if (!cmd->i)
			cmd->i = i++;
		list = list->next;
	}
}

/*
** renvoie le type en iint de la redir passee en parametre
*/

int	ft_redir_type(t_token *start)
{
	if (ft_istype(start, "simple_redir_right"))
		return (1);
	else if (ft_istype(start, "double_redir_right"))
		return (2);
	else if (ft_istype(start, "simple_redir_left"))
		return (3);
	else if (ft_istype(start, "double_redir_left"))
		return (4);
	return (0);
}
