/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:31:31 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:33:15 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_parsing2(void)
{
	ft_prep_variable();
	ft_expend_variable();
	ft_merge_alpha_var();
	ft_merge_double();
	ft_remove_space();
}

void	ft_parsing(void)
{
	ft_pretoken(g_g.inpt);
	if (g_g.error)
	{
		ft_free_toklist();
		return ;
	}
	ft_check_quotes();
	if (g_g.error)
		return ;
	ft_synerror();
	if (g_g.error)
		return ;
	ft_quotes();
	ft_heredoc();
	ft_removequotes();
	if (g_g.len == 0)
		return ;
	ft_parsing2();
	if (g_g.len == 0)
		return ;
	ft_tok_to_cmd();
	ft_gib_order();
}
