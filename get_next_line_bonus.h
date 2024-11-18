/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/18 16:59:37 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# define EOF -1
# define MAX_FD 1024
# include <stdlib.h>
# include <unistd.h>

typedef struct s_fd_state
{
	char	buf[BUFFER_SIZE];
	char	*bufp;
	ssize_t	n;
}			t_fd_state;

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	capa;
}			t_string;

int			ft_getc(int fd);
int			ft_putc(t_string *str, char c);
char		*get_next_line(int fd);

#endif