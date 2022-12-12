/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:03:50 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:03:53 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipes(t_pipes *pipes, int nbr_cmds)
{
	int	i;
	int	nbr_pipes;

	nbr_pipes = nbr_cmds - 1;
	i = 0;
	while (i < nbr_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	free_if(pipes);
}

t_pipes	*open_pipes(int nbr_cmds)
{
	int		i;
	int		nbr_pipes;
	t_pipes	*pipes;

	nbr_pipes = nbr_cmds - 1;
	pipes = (t_pipes *)ft_calloc(nbr_pipes, sizeof(t_pipes));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nbr_pipes)
	{
		if (pipe(pipes[i++]) == -1)
		{
			ft_putstr_fd("minishell: error creating pipes\n", 2);
			close_pipes(pipes, i - 1);
			free_if(pipes);
			return (NULL);
		}
	}
	return (pipes);
}
