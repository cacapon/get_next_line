/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 13:51:27 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# define COULD_NOT_READ -1
# include <stdlib.h>
# include <unistd.h>

// enum
typedef enum e_status
{
	GNL_OK = 0,
	GNL_NG = 1,
}						t_status;

typedef struct s_fd_buffer
{
	int					fd;
	char				buffer[BUFFER_SIZE];
	char				*bufp;
	size_t				buf_len;
	struct s_fd_buffer	*next;
}						t_fd_buffer;

typedef struct s_string
{
	char				*str;
	size_t				len;
	size_t				capa;
}						t_string;

// node control
t_fd_buffer				*new_fd_node(int fd);
void					add_fd_node(t_fd_buffer **head, t_fd_buffer *new_node);
void					delete_fd_node(t_fd_buffer **head, int fd);
t_fd_buffer				*find_fd_node(t_fd_buffer *head, int fd);

int						ft_getc(t_fd_buffer *fd_buf);
int						ft_putc(t_string *str, char c);
char					*get_next_line(int fd);

#endif