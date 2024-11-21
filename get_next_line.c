/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/21 11:23:38 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Write a function that returns a line read from a file descriptor
 * @param [in] fd	: file descriptor
 * @retval char* 	: Read line
 * @retval NULL		: there is nothing else to read, or an error occurred
 */
char	*get_next_line(int fd)
{
	t_string	line;
	char		c;

	line.str = NULL;
	line.capa = 0;
	line.len = 0;
	if (fd < 0)
		return (NULL);
	while (1)
	{
		c = ft_getc(fd);
		if (c == COULD_NOT_READ)
			break ;
		if (ft_putc(&line, c) == -1)
		{
			free(line.str);
			return (NULL);
		}
		if (c == '\n')
			break ;
	}
	if (line.len > 0)
		ft_putc(&line, '\0');
	return (line.str);
}
