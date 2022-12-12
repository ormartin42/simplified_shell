/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:54:53 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:51:52 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_token_typemod(char c)
{
	if (c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
		return ("space");
	else if (c == ' ')
		return ("space");
	else if (c == 0)
		return (0);
	else
		return ("alphanum");
}

t_token	*ft_getlasttokmod(t_token *start)
{
	if (!start)
		return (start);
	while (start && start->next)
		start = start->next;
	return (start);
}

void	ft_print_tokenmod(t_token *start)
{
	int			i;

	i = 1;
	while (start && start->value)
	{
		printf("token %d : value %s || type %s\n", i,
			(char *)start->value, start->type);
		start = start->next;
		i++;
	}
}

int	ft_double_redir_left(char **name)
{
	int			fd;
	static int	nb;
	char		*tmp;
	char		*tmp2;

	tmp = ft_itoa(nb);
	tmp2 = ft_strjoin("__tmp_here_doc", tmp);
	nb++;
	free(tmp);
	*name = tmp2;
	fd = open(tmp2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: error opening here_doc\n", 2);
		return (fd);
	}
	return (fd);
}
