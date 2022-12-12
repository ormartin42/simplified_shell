/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:02:02 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:02:04 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_redir_clear(t_redir *redir)
{
	free(redir->file);
	free(redir);
}

static void	ft_lstclear_redir(t_list **lst, void (*del)(t_redir *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (*lst)
	{
		del((*lst)->data);
		tmp = *lst;
		*lst = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}

static void	ft_lstclear_cmd(t_list **lst, void (*del)(t_cmd *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (*lst)
	{
		del((*lst)->data);
		tmp = *lst;
		*lst = tmp->next;
		free(tmp);
	}
	*lst = NULL;
}

static void	ft_cmd_clear(t_cmd *cmd)
{
	t_list	*tmp;
	void	(*free_pt)(void *);
	void	(*redir_pt)(t_redir *);

	free_pt = &free;
	redir_pt = &ft_redir_clear;
	tmp = cmd->args_list;
	ft_lstclear(&tmp, free_pt);
	tmp = cmd->redir_list;
	ft_lstclear_redir(&tmp, redir_pt);
	free(cmd->name);
	free(cmd);
}

void	ft_cl_clear(void)
{
	t_list	*list;
	void	(*cmd_pt)(t_cmd *);

	list = g_g.cl;
	cmd_pt = &ft_cmd_clear;
	if (!list)
		return ;
	ft_lstclear_cmd(&list, cmd_pt);
	g_g.cl = NULL;
}
