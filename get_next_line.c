/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 16:47:32 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief Copy src to dst up to strsize characters.
 *
 * @param [out] dst		: Destination memory address
 * @param [in]	src 	: Source string
 * @param [in]	srcsize	: Number of characters to copy
 * @return char* 		: dst's top pointer
 */
static char	*_strncpy(char *dst, const char *src, size_t srcsize)
{
	size_t	i;

	i = 0;
	while (i < srcsize && *src)
		dst[i++] = *src++;
	if (i < srcsize)
		dst[i] = '\0';
	return (dst);
}

/**
 * @brief
 *
 * @param fd_list
 * @param newline
 * @param fd
 * @return char*
 */
static char	*handle_error(t_fd_buffer **fd_list, t_string *newline, int fd)
{
	delete_fd_node(fd_list, fd);
	if (newline->str)
		free(newline->str);
	return (NULL);
}

/**
 * @brief one character from buf and stores it in variable c.
 *
 * @param fd_buf		: fd_buffer structures
 * @param cp			: Pointer to character variable
 * @retval PUTC_SUCCESS	: Letter C was obtained from buf
 * @retval PUTC_ERROR	: Failure to obtain character c
 * @retval PUTC_EOF		: Reach EOF
 */
t_putc_status	ft_getc(t_fd_buffer *fd_buf, unsigned char *cp)
{
	if (fd_buf->fd < 0)
		return (PUTC_ERROR);
	if (fd_buf->buf_len == 0)
	{
		fd_buf->buf_len = read(fd_buf->fd, fd_buf->buffer,
				sizeof(fd_buf->buffer));
		if (fd_buf->buf_len < 0)
			return (PUTC_ERROR);
		if (fd_buf->buf_len == 0)
			return (PUTC_EOF);
		fd_buf->bufp = fd_buf->buffer;
	}
	*cp = (unsigned char)*fd_buf->bufp++;
	fd_buf->buf_len--;
	return (PUTC_SUCCESS);
}

/**
 * @brief Adds the character c to the end of the string str.
 *
 * @param [out]	str	: The string to which the character c is added.
 * @param [in]	c	: Characters you want to add.
 * @retval 0~127	: c ASCII numbers.
 * @retval -1		: Failed to allocate.
 */
int	ft_putc(t_string *str, char c)
{
	char	*tmp;

	if (str->len + 1 >= str->capa)
	{
		str->capa = (str->len + 1) * 2;
		tmp = malloc(str->capa);
		if (!tmp)
			return (-1);
		tmp = _strncpy(tmp, str->str, str->len);
		tmp[str->len] = '\0';
		free(str->str);
		str->str = tmp;
	}
	str->str[str->len] = c;
	str->len++;
	return (c);
}

/**
 * @brief Returns a string of text in fd up to a newline.
 * @param [in] fd	: file descriptor
 * @retval char* 	: read line
 * @retval NULL		: Could not read or error
 */
char	*get_next_line(int fd)
{
	static t_fd_buffer	*fd_list = NULL;
	t_fd_buffer			*current_fd;
	t_string			newline;
	unsigned char		byte_read;
	t_putc_status		putc_result;

	current_fd = setup_fd_buffer(fd, &fd_list);
	newline = (t_string){.str = NULL, .len = 0, .capa = 0};
	while (1)
	{
		putc_result = ft_getc(current_fd, &byte_read);
		if (putc_result == PUTC_ERROR)
			return (handle_error(fd_list, &newline, fd));
		if (putc_result == PUTC_EOF || byte_read == '\n')
			break ;
		ft_putc(&newline, byte_read);
	}
	if (newline.len > 0)
		ft_putc(&newline, '\0');
	if (putc_result == PUTC_EOF)
		delete_fd_node(&fd_list, fd);
	return (newline.str);
}
