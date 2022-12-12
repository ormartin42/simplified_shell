/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ormartin <ormartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:39:52 by ormartin          #+#    #+#             */
/*   Updated: 2021/01/18 18:39:54 by ormartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	write_next_line(int ret, char **stack, char **line)
{
	char	*tmp;

	tmp = *stack;
	if (ret == 0 && !*stack)
	{
		*line = ft_strdup("");
		return (0);
	}
	if (!ft_strchr(*stack, '\n'))
	{
		*line = ft_strdup(*stack);
		free(*stack);
		*stack = NULL;
		return (0);
	}
	*line = ft_substr(tmp, 0, ft_strlen(tmp) - ft_strlen(ft_strchr(tmp, '\n')));
	*stack = ft_strdup(ft_strchr(tmp, '\n') + 1);
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	read_next_line(int fd, char **stack)
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = read(fd, buff, BUFFER_SIZE);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (*stack)
		{
			tmp = *stack;
			*stack = ft_strjoin(tmp, buff);
			free(tmp);
			tmp = NULL;
		}
		else
			*stack = ft_strdup(buff);
		if (ft_strchr(*stack, '\n'))
			break ;
		ret = read(fd, buff, BUFFER_SIZE);
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char	*stack[FD_MAX + 1];
	char		buf;
	int			ret;

	if ((fd < 0 || fd > FD_MAX) || !line || BUFFER_SIZE <= 0
		|| (read(fd, &buf, 0) < 0))
		return (-1);
	ret = read_next_line(fd, &stack[fd]);
	return (write_next_line(ret, &stack[fd], line));
}
