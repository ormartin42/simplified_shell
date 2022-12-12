/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:05:51 by ormartin          #+#    #+#             */
/*   Updated: 2020/11/16 16:06:25 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*s1;
	char		c1;

	s1 = s;
	c1 = c;
	i = 0;
	while (i < n)
	{
		if (s1[i] == c1)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}
