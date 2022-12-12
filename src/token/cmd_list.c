/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:02:08 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:05:09 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** Initialise la redir avecc le token envoye en parametre
** en identifiant le type de redir de start et recuperer la value de start->next
** comme filename
*/
static t_redir	*ft_init_redir(t_token *start)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	new->type = ft_redir_type(start);
	if (new->type == 4)
		new->file = ft_strdup(start->value);
	else
		new->file = ft_strdup(start->next->value);
	return (new);
}

/*
** avance dans la toklist depuis start et cree une liste chainee de
** struct t_redir 
*/

static t_list	*ft_init_redir_list(t_token *start)
{
	t_list	*list;
	t_redir	*redir;
	t_list	*new;
	t_token	*tok;

	list = NULL;
	tok = start;
	while (tok && !ft_istype(tok, "pipeline"))
	{
		if (ft_isredir(tok, 0))
		{
			redir = ft_init_redir(tok);
			new = ft_lstnew(redir);
			ft_lstadd_back(&list, new);
		}
		tok = tok->next;
	}
	return (list);
}

/*
** Avance dans la liste de token depuis start jusqua fin de liste ou tomber sur
** un  pipe
** le premier alphanum trouve est le "name"
** ensuite lorsque 2 alphanums se suivent le deuxieme est un argument
** kle nom ccommence la liste et est stockee dans name les arg sont add-bback
** return une liste d'argument
*/

static t_list	*ft_init_args_list(t_token *start, int flag)
{
	t_list	*list;
	t_list	*new;
	t_token	*tok;

	tok = start;
	list = NULL;
	while (tok && !ft_istype(tok, "pipeline"))
	{
		if (ft_istype(tok, "alphanum") || ft_istype(tok, "variable"))
		{
			if (flag == 1)
			{
				new = ft_lstnew(ft_strdup(tok->value));
				ft_lstadd_back(&list, new);
			}
			flag = 1;
		}
		else
			flag = 0;
		tok = tok->next;
	}
	return (list);
}

/*
** cree un element t_cmd puis appelle les differentes fonctions de remplissage
** en leur transmettant le pointeur sur le depart d' ou elles doivent iterer
** return un t_cmd
*/

static t_cmd	*ft_init_cmd(t_token *start)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->name = NULL;
	new->args_list = NULL;
	if (ft_isredir(start, 0))
	{
		new->args_list = ft_init_args_list(start, 0);
		if (new->args_list && new->args_list->data)
			new->name = ft_strdup(new->args_list->data);
	}
	else
	{
		new->name = ft_strdup(start->value);
		new->args_list = ft_init_args_list(start, 1);
	}
	new->redir_list = ft_init_redir_list(start);
	new->fd[0] = 0;
	new->fd[1] = 1;
	return (new);
}

/*
** appelle une premiere fois ft_init_cmd sur le debut de la liste de token
** cree la liste avec cet element puis avance jusqua un pipelene
** saute le pipeline et appelle ft_init_ccmd sur la suite
** attibue la liste de ccmd a la globale
*/

void	ft_tok_to_cmd(void)
{
	t_token	*start;
	t_list	*list;
	t_list	*new;

	list = NULL;
	start = g_g.start;
	new = ft_lstnew(ft_init_cmd(start));
	ft_lstadd_back(&list, new);
	while (start)
	{
		if (ft_istype(start, "pipeline"))
		{
			start = start->next;
			new = ft_lstnew(ft_init_cmd(start));
			ft_lstadd_back(&list, new);
		}
		else
			start = start->next;
	}
	g_g.cl = list;
}
