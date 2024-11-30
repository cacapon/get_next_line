/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/30 13:05:42 by ttsubo           ###   ########.fr       */
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
static char	*_ft_strncpy(char *dst, const char *src, size_t srcsize)
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
static char	*handle_error(t_fd_buf **fd_list, t_string *newline, int fd)
{
	delete_fd_node(fd_list, fd);
	if (newline->str)
		free(newline->str);
	return (NULL);
}

/**
 * @brief one character from buf and stores it in variable c.
 *
 * @param fd_buf		: fd_buf structures
 * @param cp			: Pointer to character variable
 * @retval PUTC_OK	: Letter C was obtained from buf
 * @retval PUTC_ERR	: Failure to obtain character c
 * @retval PUTC_EOF		: Reach EOF
 */
int	ft_getc(t_fd_buf *fd_buf, unsigned char *cp)
{
	if (fd_buf->fd < 0)
		return (GETC_ERR);
	if (fd_buf->buf_len == 0)
	{
		fd_buf->buf_len = read(fd_buf->fd, fd_buf->buf, sizeof(fd_buf->buf));
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
 * @param sts 
 * @retval PUTC_OK	: you was able to add one character to the line.
 * @retval PUTC_ERR	: 
 */
int	ft_putc(t_string *str, char c, t_getc_sts sts)
{
	char	*tmp;
	size_t	i;

	if (sts == GETC_EOF)
		return (PUTC_OK);
	if (sts == GETC_ERR)
		return (PUTC_ERR);
	if (str->len + 1 >= str->capa)
	{
		str->capa = (str->len + 1) * 2;
		tmp = malloc(str->capa);
		if (!tmp)
			return (PUTC_ERR);
		i = 0;
		while (i < str->capa)
			tmp[i++] = 0;
		_ft_strncpy(tmp, str->str, str->len);
		tmp[str->len] = '\0';
		free(str->str);
		str->str = tmp;
	}
	str->str[str->len] = c;
	str->len++;
	return (PUTC_OK);
}

/**
 * @brief Returns a string of text in fd up to a newline.
 * @param [in] fd	: file descriptor
 * @retval char* 	: read line
 * @retval NULL		: Could not read or error
 */
char	*get_next_line(int fd)
{
	static t_fd_buf	*fd_list = NULL;
	t_fd_buf		*current_fd;
	t_string		newline;
	unsigned char	byte_read;
	t_sts			result;

	current_fd = setup_fd_buf(fd, &fd_list);
	if (!current_fd)
		return (NULL);
	newline = (t_string){.str = NULL, .len = 0, .capa = 0};
	while (1)
	{
		result.getc_sts = ft_getc(current_fd, &byte_read);
		result.putc_sts = ft_putc(&newline, byte_read, result.getc_sts);
		set_sts(&result);
		if (result.gnl_sts == GNL_ERR)
			return (handle_error(&fd_list, &newline, fd));
		if (result.gnl_sts == GNL_EOF || byte_read == '\n')
			break ;
	}
	if (newline.len > 0)
		ft_putc(&newline, '\0', result.getc_sts);
	if (result.gnl_sts == GNL_EOF)
		delete_fd_node(&fd_list, fd);
	return (newline.str);
}
