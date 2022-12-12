/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:28:31 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 15:07:24 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	complete_line_var(char *line, char buf[BUFSIZ], int *i, int *l)
{
	char	*var_key;
	char	*var_value;
	int		j;

	(*l)++;
	j = *l;
	while (line[j] && line[j] != '$' && !ft_isspace(line[j]) && line[j] != '/')
		j++;
	var_key = ft_substr(line, (*l), j - (*l));
	if (!ft_strcmp(var_key, "?"))
		var_value = search_var(g_g.exitstatus, var_key);
	else
		var_value = search_var(g_g.env, var_key);
	if (!var_value)
		reset_buf(buf, i);
	else
		get_var_value(buf, var_value, i);
	(*l) += j - (*l);
	free(var_key);
}

void	complete_dollar_sign(char *line, char buf[BUFSIZ], int *i, int *l)
{
	buf[*i] = line[*l];
	(*i)++;
	(*l)++;
}

char	*ft_expendline(char *line)
{
	int		i;
	int		l;
	char	buf[1024];
	char	*exp_line;

	i = 0;
	l = 0;
	while (line[l])
	{
		complete_line_spaces(line, buf, &i, &l);
		if (line[l] == '$' && (!line[l + 1] || ft_isspace(line[l + 1])))
			complete_dollar_sign(line, buf, &i, &l);
		else if (line[l] == '$' && line[l + 1])
			complete_line_var(line, buf, &i, &l);
		else
			complete_line_alphanum(line, buf, &i, &l);
	}
	buf[i] = '\0';
	exp_line = (char *)ft_calloc(sizeof(char), i);
	if (!exp_line)
		return (NULL);
	exp_line = ft_strdup(buf);
	free_if(line);
	return (exp_line);
}	
