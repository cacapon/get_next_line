/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/21 13:20:37 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	_gnl_init(t_string *line)
{
	line->str = NULL;
	line->capa = 0;
	line->len = 0;
}

static int	_gnl_exec(t_fd_state **fd_list, t_fd_state *state, t_string *line,
		char *c)
{
	*c = ft_getc(state);
	if (*c == COULD_NOT_READ)
	{
		remove_fd_node(fd_list, state->fd);
		return (IS_BREAK);
	}
	if (ft_putc(line, *c) == -1)
	{
		remove_fd_node(fd_list, state->fd);
		free(line->str);
		return (IS_NULL);
	}
	if (*c == '\n')
		return (IS_BREAK);
	return (0);
}

/**
 * @brief Write a function that returns a line read from a file descriptor
 * @param [in] fd	: file descriptor
 * @retval char* 	: Read line
 * @retval NULL		: there is nothing else to read, or an error occurred
 */
char	*get_next_line(int fd)
{
	static t_fd_state	*fd_list = NULL;
	t_fd_state			*state;
	t_string			line;
	char				c;
	int					result;

	if (fd < 0)
		return (NULL);
	state = get_fd_node(&fd_list, fd);
	if (!state)
		return (NULL);
	_gnl_init(&line);
	while (1)
	{
		result = _gnl_exec(&fd_list, state, &line, &c);
		if (result == IS_NULL)
			return (NULL);
		if (result == IS_BREAK)
			break ;
	}
	if (line.len > 0)
		ft_putc(&line, '\0');
	return (line.str);
}
