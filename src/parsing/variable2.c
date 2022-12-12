/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscandol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:44:43 by tscandol          #+#    #+#             */
/*   Updated: 2021/12/16 14:01:47 by tscandol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_splitmod2(char **tab, char *tmp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tmp[++i] && tmp[i] != '=')
		tab[0][i] = tmp[i];
	tab[0][i] = '\0';
	while (tmp[i])
		tab[1][j++] = tmp[i++];
	tab[1][j] = '\0';
	tab[2] = NULL;
}

char	**ft_splitmod(t_token *start)
{
	int		i;
	char	*tmp;
	char	**tab;

	i = 0;
	tmp = start->value;
	if (!ft_strchr(start->value, '='))
		return (NULL);
	tab = malloc(3 * sizeof(char *));
	if (!tab)
		return (NULL);
	while (tmp[i] != '=')
		i++;
	tab[0] = malloc((i + 1) * sizeof(char));
	if (!tab[0])
		return (NULL);
	tab[1] = malloc((ft_strlen(tmp) - i + 1) * sizeof(char));
	if (!tab[1])
		return (NULL);
	ft_splitmod2(tab, tmp);
	return (tab);
}

static void	ft_expend_variable3s(t_token *start, char *tmp, char **tab)
{
	ft_change_value(start, tmp);
	free(tmp);
	free_array(tab);
}

int	ft_expend_variable3(t_token **start, char **tab)
{
	t_list	*env;
	t_var	*var;
	char	*tmp;

	env = g_g.env;
	while (env && env->data)
	{
		var = env->data;
		if (!ft_strcmp(tab[0], var->key))
		{
			tmp = tab[0];
			tab[0] = ft_strdup(var->value);
			free(tmp);
			break ;
		}
		env = env->next;
	}
	if (!env)
		tmp = ft_strjoin(NULL, tab[1]);
	else
		tmp = ft_strjoin(tab[0], tab[1]);
	ft_expend_variable3s(*start, tmp, tab);
	*start = (*start)->next;
	return (0);
}
