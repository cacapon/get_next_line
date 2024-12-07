/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/12/07 16:55:22 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief one character from buf and stores it in variable c.
 *
 * @param fd_buf		: fd_buf structures
 * @param cp			: Pointer to character variable
 * @retval PUTC_OK		: Letter C was obtained from buf
 * @retval PUTC_ERR		: Failure to obtain character c
 * @retval PUTC_EOF		: Reach EOF
 * @note	<pre> fd_buf != NULL
 */
static int	_ft_getc(t_buf *fd_buf, unsigned char *cp)
{
	if (fd_buf->buf_len == 0)
	{
		fd_buf->buf_len = read(fd_buf->fd, fd_buf->buf, BUFFER_SIZE);
		if (fd_buf->buf_len < 0)
			return (GETC_ERR);
		if (fd_buf->buf_len == 0)
			return (GETC_EOF);
		fd_buf->bufp = fd_buf->buf;
	}
	*cp = (unsigned char)*fd_buf->bufp++;
	fd_buf->buf_len--;
	return (GETC_OK);
}

/**
 * @brief Adds the character c to the end of the string str.
 *
 * @param [out]	str	: The string to which the character c is added.
 * @param [in]	c	: Characters you want to add.
 * @param sts 		: getc status.
 * @retval PUTC_OK	: you was able to add one character to the line.
 * @retval PUTC_ERR	: Memory allocation failure/putc failed
 */
static int	_ft_putc(t_string *line, char c, t_getc_sts sts)
{
	char	*tmp;

	if (sts == GETC_EOF)
		return (PUTC_OK);
	if (sts == GETC_ERR)
		return (PUTC_ERR);
	if (line->len + 1 >= line->capa)
	{
		line->capa = (line->len + 1) * 2;
		tmp = malloc(line->capa);
		if (!tmp)
			return (PUTC_ERR);
		gnl_memset(tmp, 0, line->capa);
		gnl_strncpy(tmp, line->str, line->len);
		tmp[line->len] = '\0';
		free(line->str);
		line->str = tmp;
	}
	line->str[line->len] = c;
	line->len++;
	return (PUTC_OK);
}

/**
 * @brief 
 * 
 * @param s_buf 
 * @param fd 
 * @return t_buf* 
 */
static t_buf	*_ft_buf_init(t_buf **s_buf, int fd)
{
	if (!s_buf)
		return (NULL);
	if (!*s_buf)
	{
		*s_buf = malloc(sizeof(t_buf));
		if (!*s_buf)
			return (NULL);
		(*s_buf)->buf = malloc(BUFFER_SIZE);
		if (!(*s_buf)->buf)
		{
			free(s_buf);
			*s_buf = NULL;
			return (NULL);
		}
		gnl_memset((*s_buf)->buf, 0, BUFFER_SIZE);
		(*s_buf)->buf_len = 0;
		(*s_buf)->bufp = (*s_buf)->buf;
		(*s_buf)->fd = fd;
	}
	return (*s_buf);
}

/**
 * @brief 
 * 
 * @param s_buf 
 */
static void	_ft_buf_free(t_buf **s_buf)
{
	if (!s_buf)
		return ;
	if (*s_buf)
	{
		if ((*s_buf)->buf)
		{
			free((*s_buf)->buf);
			(*s_buf)->buf = NULL;
		}
		free(*s_buf);
		*s_buf = NULL;
	}
}

/**
 * @brief Returns a string of text in fd up to a newline.
 * @param [in] fd	: file descriptor
 * @retval char* 	: read line
 * @retval NULL		: Could not read or error
 */
char	*get_next_line(int fd)
{
	static t_buf	*buf[MAX_FD];
	t_string		newline;
	unsigned char	uc;
	t_sts			result;

	if ((fd < 0 || MAX_FD - 1 < fd) || BUFFER_SIZE <= 0)
		return (NULL);
	if (!_ft_buf_init(&buf[fd], fd))
		return (NULL);
	newline = (t_string){.str = NULL, .len = 0, .capa = 0};
	while (1)
	{
		result.getc_sts = _ft_getc(buf[fd], &uc);
		result.putc_sts = _ft_putc(&newline, uc, result.getc_sts);
		set_sts(&result);
		if (result.gnl_sts == GNL_ERR)
			return (NULL);
		if (result.gnl_sts == GNL_EOF || uc == '\n')
			break ;
	}
	if (newline.len > 0)
		_ft_putc(&newline, '\0', result.getc_sts);
	if (result.gnl_sts == GNL_EOF)
		_ft_buf_free(&buf[fd]);
	return (newline.str);
}
