/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:34:55 by ormartin          #+#    #+#             */
/*   Updated: 2021/01/06 15:30:16 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dest_len;

	dest_len = ft_strlen(dst);
	if (dstsize <= dest_len)
		return (dstsize + ft_strlen(src));
	ft_strncat(dst, src, dstsize - dest_len - 1);
	return (dest_len + ft_strlen(src));
}
