/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 18:19:40 by ormartin          #+#    #+#             */
/*   Updated: 2021/01/18 18:30:16 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	a;
	int	b;

	i = 1;
	a = 1;
	b = 1;
	while (i < length)
	{
		if (f(tab[i - 1], tab[i]) < 0)
			a = 0;
		if (f(tab[i - 1], tab[i]) > 0)
			b = 0;
		i++;
	}
	return (a || b);
}
