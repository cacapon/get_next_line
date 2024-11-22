/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/22 15:00:36 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# define IS_NULL -1
# define IS_BREAK -2
# define COULD_NOT_READ -1
# include <stdlib.h>
# include <unistd.h>

struct	s_fd_state;

typedef struct s_fd_state
{
	int					fd;
	char				buf[BUFFER_SIZE];
	char				*bufp;
	ssize_t				n;
	struct s_fd_state	*next;
}						t_fd_state;

typedef struct s_string
{
	char				*str;
	size_t				len;
	size_t				capa;
}						t_string;

t_fd_state				*get_fd_node(t_fd_state **fd_list, int fd);
void					remove_fd_node(t_fd_state **fd_list, int fd);
int						ft_getc(t_fd_state *state);
int						ft_putc(t_string *str, char c);
char					*get_next_line(int fd);

#endif