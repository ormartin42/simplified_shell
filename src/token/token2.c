/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retoken.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:14:15 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/08 15:52:07 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
** FT_PRETOKEN : predecoupe l'input utilisateur
** INPUT : le char * Input :  input utilisateur
** 1 : Le decoupe char par char et ajoute un '\0' apres chaque char.
** 2 : l'envoie a ft_token
** OUTPUT: "char buf[2]" :  contenant 1 char suivi de '\0'
*/

void	ft_pretoken(char *inpt)
{
	int		i;
	char	buf[2];

	i = -1;
	while (inpt[++i])
	{
		buf[0] = inpt[i];
		buf[1] = '\0';
		ft_token(buf);
	}
}

/*
** FT_RETOKEN : viens adapter le type des tokens alphanums de la liste
** INPUT : "t_token *start" : liste de tokens avec types attribues
** 1 : passe le liste est attribue cmd au commande
** 2 : attribue arg au alphanums qui suivent les commandes
** 3 : attribue rarg au alphanums qui suivent les redirs (pipes exclus)
** OUTPUT : "t_token *start" : liste de tokens avec alphanums remplaces
** FCT HORS.C : ft_istype, ft_change_type -> token/token_type_value.c
*/

static void	ft_retoken1(int i, t_token *start, int *flag, int *cmd)
{
	if (i == 0)
	{
		ft_change_type(start, "cmd");
		*flag = 1;
		*cmd = 1;
	}
	else
	{
		*flag = 1;
		ft_change_type(start, "rarg");
		if (*cmd == 0)
			*flag = 0;
	}
}

void	ft_retoken(void)
{
	t_token	*start;
	int		flag;
	int		cmd;

	cmd = 0;
	flag = 0;
	start = g_g.start;
	while (start)
	{
		if (ft_istype(start, "pipeline"))
			flag = 0;
		else if (ft_isredir(start, 0))
			flag = 2;
		else if (flag == 0 && ft_istype(start, "alphanum"))
			ft_retoken1(0, start, &flag, &cmd);
		else if (flag == 1 && ft_istype(start, "alphanum"))
			ft_change_type(start, "arg");
		else if (flag == 2 && ft_istype(start, "alphanum"))
			ft_retoken1(1, start, &flag, &cmd);
		start = start->next;
	}
}
