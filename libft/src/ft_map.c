/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:17:59 by ormartin          #+#    #+#             */
/*   Updated: 2021/01/18 18:34:51 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	*range;
	int	i;

	i = -1;
	range = malloc(length * sizeof(char));
	if (!range)
		return (NULL);
	while (++i < length)
		range[i] = f(tab[i]);
	return (range);
}
