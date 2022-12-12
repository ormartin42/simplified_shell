/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:53:10 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:46:57 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_PRINT_TOKEN : print la value et le type de chaque token dans l'ordre
** INPUT : "t_token *start" : liste de token contenue dans g.start
** 1 : avance dans start et print value + type suivi de '\n'
** OUTPUT : NICHTS
*/

void	ft_print_token(void)
{
	t_token	*start;
	int		i;

	i = 1;
	start = g_g.start;
	while (start && start->value)
	{
		printf("token %d : value %s || type %s\n", i, \
				(char *)start->value, start->type);
		start = start->next;
		i++;
	}
}

/*
** FT_REVPRINT_TOKEN : print chaque token dans l'ordre inverse pour test revlink
** INPUT : "t_token *start" : liste de token contenue dans g.start
** 1 : va jusqu'au bout de la liste avec ft_get_lasttok
** 2 : print value + type suivi de '\n'
** OUTPUT : NICHTS
** FCT HORS .c : ft_get_lasttok -> token/tokenutils.c
*/

void	ft_revprint_token(void)
{
	t_token	*start;

	start = ft_get_lasttok();
	while (start && start->value)
	{
		printf("token: value %s || type %s\n", \
				(char *)start->value, start->type);
		start = start->prev;
	}
}

/*
** recupere la globale et printe chacun de ses elements t_cmd en affichant :
** Nom\n
** Arguments(premeier element est NAME) : ARG1 | ARG2 | ...\n
** Redirections : type1 / filename1\n
** type2 / filename2\n etc
*/

static void	ft_print_cl2(t_cmd *cmd, t_list *redir)
{
	t_redir	*red;

	printf("\nREDIRLIST :\n");
	while (redir)
	{
		red = redir->data;
		printf("type : %d / file |%s|\n", red->type, red->file);
		redir = redir->next;
	}
	printf("\nFDS :\n");
	printf("FD[0] = %d\n", cmd->fd[0]);
	printf("FD[1] = %d\n", cmd->fd[1]);
	printf("------------------------------------------\n");
}

void	ft_print_cl(void)
{
	t_list	*cl;
	t_cmd	*cmd;
	t_list	*redir;
	t_list	*args;

	cl = g_g.cl;
	while (cl)
	{
		cmd = cl->data;
		printf("\n ---------element of commandlist--------\n");
		args = cmd->args_list;
		printf("NAME : |%s|\n", cmd->name);
		printf("ARGLIST :");
		while (args)
		{
			printf(" |%s|", (char *)args->data);
			args = args->next;
		}
		redir = cmd->redir_list;
		ft_print_cl2(cmd, redir);
		cl = cl->next;
	}
}
