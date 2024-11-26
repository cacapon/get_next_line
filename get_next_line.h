/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/26 13:24:09 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// using read(), malloc()
# include <stdlib.h>
# include <unistd.h>

// enum
typedef enum e_status
{
	STATUS_OK = 0,
	STATUS_NG = 1,
}						t_status;

typedef enum e_fd_exist
{
	FD_EXIST = 1,
	FD_NOT_EXIST = 0
}						t_fd_exist;

struct	s_fd_info;

typedef struct s_fd_info
{
	int					fd;
	char				*buf;
	ssize_t				buf_len;
	char				*line;
	ssize_t				line_len;
	ssize_t				line_capa;
	struct s_fd_info	*next;
}						t_fd_info;

// prototype

t_status	ft_getbuf(t_fd_info *fd_info);

// typedef struct s_buffer_info
// {
	
// }

// typedef struct s_fd_state
// {
// 	int					fd;
// 	char				buf[BUFFER_SIZE];
// 	char				*bufp;
// 	ssize_t				n;
// 	struct s_fd_state	*next;
// }						t_fd_state;

// typedef struct s_string
// {
// 	char				*str;
// 	size_t				len;
// 	size_t				capa;
// }						t_string;

#endif
