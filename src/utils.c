/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:06:04 by ormartin          #+#    #+#             */
/*   Updated: 2021/12/14 07:07:39 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_if(void *elem)
{
	if (elem)
	{
		free(elem);
		elem = NULL;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	while (array[++i])
		free_if(array[i]);
	free_if(array);
	array = NULL;
}

int	tablen(char **array)
{
	int	len;

	len = 0;
	while (*array)
	{
		len++;
		array++;
	}
	return (len);
}
