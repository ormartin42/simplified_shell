/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:05:36 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/16 06:05:35 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*
**	Fonction pour recuperer l'input de l'utilisateur + initialiser
**	l'historique. Grace a readline on a acces a add_history, et 
**	cette fonction permet aussi la completion des inputs grace a TAB.
**	ATTENTION: readline cree des leaks mais c'est specifie dans le
**	sujet que pas besoin de s'en occuper.
*/

static void	get_input_line(void)
{
	free_if(g_g.inpt);
	if (g_g.signal == 1)
		g_g.inpt = readline("");
	else
		g_g.inpt = readline("minishell> ");
	if (g_g.inpt && *g_g.inpt && !g_g.signal)
		add_history(g_g.inpt);
	g_g.signal = 0;
	g_g.fork = 0;
}

static int	init_minishell(int argc, char **envp)
{
	if (argc != 1 || !isatty(0) || parse_env(envp, &g_g.env))
	{
		if (argc != 1)
			ft_putstr_fd("minishell: wrong number of arguments\n", 2);
		else if (!isatty(0))
			ft_putstr_fd("minishell: not a valid terminal\n", 2);
		else
			ft_putstr_fd("minishell: error parsing environment\n", 2);
		return (EXIT_FAILURE);
	}
	init_var();
	init_signal();
	errno = 0;
	g_g.error = 0;
	g_g.inpt = NULL;
	g_g.hd_sign = 0;
	return (EXIT_SUCCESS);
}

static void	minishell_loop(void)
{
	while (1)
	{
		g_g.len = 0;
		g_g.start = NULL;
		g_g.hd_sign = 0;
		get_input_line();
		if (!g_g.inpt)
		{
			exit_msg_handler();
			break ;
		}
		if (*g_g.inpt)
			ft_parsing();
		if (g_g.error)
		{
			free_and_restart();
			continue ;
		}
		exec_handler(g_g.cl, &g_g.env);
		if (g_g.start && !ft_strcmp(g_g.start->value, "exit"))
			break ;
		free_and_restart();
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (init_minishell(argc, envp) == FALSE)
		return (EXIT_FAILURE);
	minishell_loop();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (free_all_and_exit());
}
