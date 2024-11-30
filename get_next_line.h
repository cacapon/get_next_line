/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/30 13:20:00 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

# if BUFFER_SIZE <= 0
#  error "BUFFER_SIZE must be greater than 0"
# endif

// enum
typedef enum e_gnl_common_sts
{
	GNL_OK = 0,
	GNL_NG = 1,
}					t_gnl_common_sts;

typedef enum e_gnl_sts
{
	GNL_INIT,
	GNL_READ,
	GNL_EOF,
	GNL_ERR,
}					t_gnl_sts;

typedef enum e_getc_sts
{
	GETC_ERR = -1,
	GETC_EOF = 0,
	GETC_OK = 1,
}					t_getc_sts;

typedef enum e_putc_sts
{
	PUTC_ERR = -1,
	PUTC_OK = 1,
}					t_putc_sts;

// struct

typedef struct s_sts
{
	t_gnl_sts		gnl_sts;
	t_getc_sts		getc_sts;
	t_putc_sts		putc_sts;
}					t_sts;

typedef struct s_fd_buf
{
	int				fd;
	char			*buf;
	char			*bufp;
	size_t			buf_len;
	struct s_fd_buf	*next;
}					t_fd_buf;

typedef struct s_string
{
	char			*str;
	size_t			len;
	size_t			capa;
}					t_string;

// util function
int					delete_fd_node(t_fd_buf **head, int fd);
t_fd_buf			*setup_fd_buf(int fd, t_fd_buf **fd_list);
t_sts				*set_sts(t_sts *result);

// get_next_line
char				*get_next_line(int fd);

#endif