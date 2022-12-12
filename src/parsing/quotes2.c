/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:47:45 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:00:15 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_removequotes(void)
{
	t_token	*start;
	t_token	*tmp;

	start = g_g.start;
	while (start)
	{
		if (ft_istype(start, "single_quote")
			|| ft_istype(start, "double_quote"))
		{
			tmp = start->next;
			ft_remove_token(start);
			start = tmp;
		}
		else
			start = start->next;
	}
}
