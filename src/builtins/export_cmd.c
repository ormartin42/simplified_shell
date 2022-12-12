/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:55:39 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:00:21 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	add_or_append_var(t_list **env, char *key, char *str, int app)
{
	if (!*str && *(str - 1) != '=')
		edit_var(env, key, NULL);
	else
	{
		if (app)
			append_var(env, key, str);
		else
			edit_var(env, key, str);
	}	
}

static int	keylen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '_' || ft_isalnum(str[i])))
		i++;
	if (!i || (str[i] != '=' && ft_strncmp(str + i, "+=", 2) && str[i] != 0))
		return (-1);
	return (i);
}

static char	*get_key(char **str, int *append)
{
	int		i;
	char	*dest;

	if (ft_isdigit(**str))
		return (NULL);
	i = keylen(*str);
	if (i < 0)
		return (NULL);
	if (!ft_strncmp((*str) + i, "+=", 2))
		*append = 1;
	else
		*append = 0;
	dest = ft_substr(*str, 0, i);
	if (!dest)
		return (NULL);
	if ((*str)[i])
		(*str)++;
	(*str) += i + *append;
	return (dest);
}

static int	export_arg(char *arg, t_list **env)
{
	char	*str;
	char	*key;
	int		append;

	str = arg;
	key = get_key(&str, &append);
	if (!key)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (EXIT_FAILURE);
	}
	else
		add_or_append_var(env, key, str, append);
	free_if(key);
	return (EXIT_SUCCESS);
}

int	export_cmd(int len, char **args, t_list **env)
{
	int	i;

	if (len == 1)
		return (print_sorted_env(*env));
	i = 1;
	while (i < len)
	{
		if (export_arg(args[i], env))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
