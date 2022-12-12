/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:03:11 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:03:16 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
**	check_executable permet de checker si la cmd n'est pas un path 
**	valide en elle-meme, en verifiant bien qu'il ne s'agisse pas d'un
**	directory et bien d'un executable, et que nous avons les droits 
**	necessaires pour l'executer. 
*/

static void	print_error_msg(char *cmd, char *err, int *ret, int errnum)
{
	if (errnum == 2)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (cmd)
			ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (err)
			ft_putstr_fd(err, 2);
		ft_putstr_fd("\n", 2);
	}
	*ret = errnum;
}

static int	display_error_msg(int err, char *cmd)
{
	int		ret;
	char	*exitstatus;	

	ret = 0;
	if (err == 1)
		print_error_msg(NULL, NULL, &ret, 2);
	else if (err == 2)
		print_error_msg(cmd, "is a directory", &ret, 126);
	else if (err == 3)
		print_error_msg(cmd, "Permission denied", &ret, 126);
	else
		print_error_msg(cmd, "No such file or directory", &ret, 127);
	exitstatus = ft_itoa(ret);
	edit_var(&g_g.exitstatus, "?", exitstatus);
	free_if(exitstatus);
	return (ret);
}

/*
**  Si la cmd n'est pas dans nos builtins, on va check si la cmd est un absolute
**  path vers la cmd elle-meme, et sinon on va checker dans la variable PATH les
**  dossiers un par un (de gauche a droite) pour voir si on retrouve la cmd
**  specifiee dans l'un d'entre eux. Si oui, on remplace la cmd par le path
**  absolu vers la commande en question.
*/

static int	find_bin(char **abs_path, char **cmd, char **paths)
{
	int			i;
	char		*bin;

	i = -1;
	while (paths[++i])
	{
		bin = (char *)ft_calloc(ft_strlen(paths[i]) + ft_strlen(cmd[0]) + 2,
				sizeof(char));
		if (!bin)
			break ;
		ft_strcat(bin, paths[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
		if (!access(bin, F_OK))
			break ;
		free_if(bin);
		bin = NULL;
	}
	free_array(paths);
	if (!bin)
		return (EXIT_FAILURE);
	free_if(cmd[0]);
	cmd[0] = bin;
	*abs_path = ft_strdup(bin);
	return (EXIT_SUCCESS);
}

static int	check_executable(char **abs_path, char **cmd)
{
	struct stat	sb;
	DIR			*dir;

	if (cmd[0][0] == '.' && !cmd[0][1])
		return (display_error_msg(1, cmd[0]));
	if (!ft_strcmp(cmd[0], "/") || !ft_strcmp(cmd[0], "./"))
		return (display_error_msg(2, cmd[0]));
	dir = opendir(cmd[0]);
	if (dir)
	{
		closedir(dir);
		return (display_error_msg(2, cmd[0]));
	}
	if (stat(cmd[0], &sb) == 0 && sb.st_mode & S_IXUSR)
	{
		*abs_path = ft_strdup(cmd[0]);
		return (EXIT_SUCCESS);
	}
	if (!access(cmd[0], F_OK))
		return (display_error_msg(3, cmd[0]));
	return (display_error_msg(4, cmd[0]));
}

int	get_absolute_path(char **abs_path, char **cmd, t_list *env)
{
	char	**paths;

	paths = NULL;
	if (!cmd || !*cmd)
		return (EXIT_FAILURE);
	if (cmd[0][0] == '.' || cmd[0][0] == '/' || !ft_strncmp(cmd[0], "./", 2))
		return (check_executable(abs_path, cmd));
	paths = ft_split(search_var(env, "PATH"), ':');
	if (!paths)
		return (EXIT_FAILURE);
	return (find_bin(abs_path, cmd, paths));
}
