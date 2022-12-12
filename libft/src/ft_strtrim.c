/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 19:21:41 by ormartin          #+#    #+#             */
/*   Updated: 2020/11/18 12:20:35 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		size_str;
	char		*strtrim;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size_str = ft_strlen(s1);
	while (size_str && ft_strchr(set, s1[size_str]))
		size_str--;
	strtrim = ft_substr((char *)s1, 0, size_str + 1);
	return (strtrim);
}
