/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_myatoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:30:56 by ormartin          #+#    #+#             */
/*   Updated: 2021/01/18 18:33:24 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_myatoi(char *str)
{
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	while (*str && (*str == '\n' || *str == '\f' || *str == '\r'
			|| *str == '\t' || *str == '\v' || *str == ' '))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		++str;
	}
	return (num * sign);
}
