/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/12/07 17:03:55 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// define
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif
# ifndef MAX_FD
#  define MAX_FD 256
# endif

// include
# include <stdlib.h>
# include <unistd.h>

// enum
typedef enum e_gnl_sts
{
	GNL_INIT,
	GNL_READ,
	GNL_EOF,
	GNL_ERR,
}				t_gnl_sts;

typedef enum e_getc_sts
{
	GETC_ERR = -1,
	GETC_EOF = 0,
	GETC_OK = 1,
}				t_getc_sts;

typedef enum e_putc_sts
{
	PUTC_ERR = -1,
	PUTC_OK = 1,
}				t_putc_sts;

// struct

typedef struct s_sts
{
	t_gnl_sts	gnl_sts;
	t_getc_sts	getc_sts;
	t_putc_sts	putc_sts;
}				t_sts;

typedef struct s_buf
{
	int			fd;
	char		*buf;
	char		*bufp;
	ssize_t		buf_len;
}				t_buf;

typedef struct s_string
{
	char		*str;
	size_t		len;
	size_t		capa;
}				t_string;

// util function
t_sts			*set_sts(t_sts *result);
void			*gnl_memset(void *b, int c, size_t len);
char			*gnl_strncpy(char *dst, const char *src, size_t srcsize);
void			*gnl_calloc(size_t count, size_t size);

// get_next_line
char			*get_next_line(int fd);

#endif
