/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 18:01:56 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# include <stdlib.h>
# include <unistd.h>

# if BUFFER_SIZE <= 0
#  error "BUFFER_SIZE must be greater than 0"
# endif

// enum

// Generic state management enum
typedef enum e_gnl_status
{
	GNL_OK = 0,
	GNL_NG = 1,
}						t_gnl_status;

// State management enum for getc
typedef enum e_getc_status
{
	GETC_ERROR = -1,
	GETC_EOF = 0,
	GETC_SUCCESS = 1,
}						t_getc_status;

//State management enum for putc
typedef enum e_putc_status
{
	PUTC_ERROR = -1,
	PUTC_SUCCESS = 1,
}						t_putc_status;

// struct

// state-controlling structure
typedef struct s_status
{
	t_gnl_status		gnl_sts;
	t_getc_status		getc_sts;
	t_putc_status		putc_sts;
}						t_status;

typedef struct s_fd_buffer
{
	int					fd;
	char				*buffer;
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
int						add_fd_node(t_fd_buffer **head, t_fd_buffer *new_node);
int						delete_fd_node(t_fd_buffer **head, int fd);
t_fd_buffer				*find_fd_node(t_fd_buffer *head, int fd);
t_fd_buffer				*setup_fd_buffer(int fd, t_fd_buffer **fd_list);

// get_next_line
t_putc_status			ft_getc(t_fd_buffer *fd_buf, unsigned char *cp);
int						ft_putc(t_string *str, char c, t_getc_status sts);
char					*get_next_line(int fd);

#endif