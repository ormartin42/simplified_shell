/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:52:58 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 06:53:01 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	change_to_oldpwd(t_list **env)
{
	char	*oldpwd;
	char	pwd[PATH_MAX + 1];

	oldpwd = search_var(*env, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (EXIT_FAILURE);
	}
	getcwd(pwd, sizeof(pwd));
	if (chdir(oldpwd) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(oldpwd);
		free_if(oldpwd);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(oldpwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	edit_var(env, "OLDPWD", pwd);
	edit_var(env, "PWD", oldpwd);
	return (EXIT_SUCCESS);
}

static int	change_to_new_dir(t_list **env, char *arg)
{
	char	pwd[PATH_MAX + 1];

	getcwd(pwd, sizeof(pwd));
	if (chdir(arg) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(arg);
		return (EXIT_FAILURE);
	}
	edit_var(env, "OLDPWD", pwd);
	ft_memset(pwd, ft_strlen(pwd), sizeof(pwd));
	getcwd(pwd, sizeof(pwd));
	edit_var(env, "PWD", pwd);
	return (EXIT_SUCCESS);
}

static int	change_to_home(t_list **env)
{
	char	*home;
	char	pwd[PATH_MAX + 1];
	char	oldpwd[PATH_MAX + 1];

	getcwd(oldpwd, sizeof(oldpwd));
	home = search_var(*env, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(home);
		return (EXIT_FAILURE);
	}
	edit_var(env, "OLDPWD", oldpwd);
	getcwd(pwd, sizeof(pwd));
	edit_var(env, "PWD", pwd);
	return (EXIT_SUCCESS);
}

/*
** CD pour changer de dossier. Differentes fonctions pour gerer les
** cas specifiques lies aux differents nombres d'arguments.
*/

int	cd_cmd(int len, char **args, t_list **env)
{
	if (len == 1 || (len == 2 && !ft_strcmp(args[1], "~")))
		return (change_to_home(env));
	else if (len == 2 && !ft_strcmp(args[1], "-"))
		return (change_to_oldpwd(env));
	else
		return (change_to_new_dir(env, args[1]));
}
