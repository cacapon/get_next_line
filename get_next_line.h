/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/26 13:58:03 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

// using read(), malloc(), free()
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

char		*get_next_line(int fd);
t_status	ft_getbuf(t_fd_info *fd_info);
t_status	ft_putline(t_fd_info *fd_info);
t_status	ft_contain_linebreak(char *str);

#endif
