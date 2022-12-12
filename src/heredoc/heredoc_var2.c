/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:54:38 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 15:09:34 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

void	complete_line_alphanum(char *line, char buf[BUFSIZ], int *i, int *l)
{
	while (line[*l] && line[*l] != '$')
	{
		buf[*i] = line[*l];
		(*i)++;
		(*l)++;
	}
}

void	complete_line_spaces(char *line, char buf[BUFSIZ], int *i, int *l)
{
	while (ft_isspace(line[*l]))
	{
		buf[*i] = line[*l];
		(*i)++;
		(*l)++;
	}
}

void	reset_buf(char buf[BUFSIZ], int *i)
{
	ft_memset(buf, 0, sizeof(char) * BUFSIZ);
	buf[0] = ' ';
	(*i) = 1;
}

void	get_var_value(char buf[BUFSIZ], char *var_value, int *i)
{
	while (*var_value)
	{
		buf[*i] = *var_value;
		(*i)++;
		var_value++;
	}
}
