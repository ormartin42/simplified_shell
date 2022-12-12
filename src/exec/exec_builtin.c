/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:02:33 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:02:35 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**args_list_to_tab(t_list *args_list)
{
	char	**tab;
	int		i;

	tab = (char **)ft_calloc(ft_lstsize(args_list) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (args_list)
	{
		tab[i] = ft_strdup(args_list->data);
		i++;
		args_list = args_list->next;
	}
	tab[i] = 0;
	return (tab);
}

int	check_builtin(char *cmd)
{
	int			i;
	const char	*bi[] = {"echo", "cd", "pwd", "export", \
						"unset", "env", "exit", NULL};

	i = 0;
	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	while (bi[i])
	{
		if (!ft_strcmp(bi[i], cmd))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

int	exec_builtin(char *name, t_list *args_list, t_cmd *cmd, t_list **env)
{
	int		ret;
	char	**args;

	if (handle_redirections(cmd, cmd->fd) == FALSE)
		return (EXIT_FAILURE);
	args = args_list_to_tab(args_list);
	if (!ft_strcmp(name, "echo"))
		ret = echo_cmd(tablen(args), args);
	else if (!ft_strcmp(name, "cd"))
		ret = cd_cmd(tablen(args), args, env);
	else if (!ft_strcmp(name, "pwd"))
		ret = pwd_cmd();
	else if (!ft_strcmp(name, "export"))
		ret = export_cmd(tablen(args), args, env);
	else if (!ft_strcmp(name, "unset"))
		ret = unset_cmd(tablen(args), args, env);
	else if (!ft_strcmp(name, "env"))
		ret = env_cmd(*env);
	else
		ret = exit_cmd(tablen(args), args);
	reinit_redirections(cmd->fd);
	free_array(args);
	return (ret);
}
