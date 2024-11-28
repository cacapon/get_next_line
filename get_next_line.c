/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 13:53:49 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TODO: ft_getcが持っているfdの管理をget_next_line側で持つ
// TODO: stateの連結リスト化
// TODO: BUFをヒープで管理するようにする

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
	return (dst);
}

static t_fd_buffer	*_setup_fd_buffer(int fd, t_fd_buffer **fd_list)
{
	t_fd_buffer	*current_fd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_fd = find_fd_node(*fd_list, fd);
	if (!current_fd)
	{
		current_fd = new_fd_node(fd);
		if (!current_fd)
			return (NULL);
		add_fd_node(fd_list, current_fd);
	}
	return (current_fd);
}

int	ft_getc(t_fd_buffer *fd_buf)
{
	if (fd_buf->fd < 0)
		return (COULD_NOT_READ);
	if (fd_buf->buf_len == 0)
	{
		fd_buf->buf_len = read(fd_buf->fd, fd_buf->buffer,
				sizeof(fd_buf->buffer));
		if (fd_buf->buf_len <= 0)
			return (COULD_NOT_READ);
		fd_buf->bufp = fd_buf->buffer;
	}
	fd_buf->buf_len--;
	return ((unsigned char)*fd_buf->bufp++);
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
		free(str->str);
		str->str = tmp;
	}
	str->str[str->len] = c;
	str->len++;
	return (c);
}

/**
 * @brief fdのテキストのうち、改行までの文字列を返します。
 * @param [in] fd	: ファイルディスクリプタ
 * @retval char* 	: 読み込んだ行
 * @retval NULL		: 読めなかった・もしくはエラーだった場合
 */
char	*get_next_line(int fd)
{
	static t_fd_buffer	*fd_list = NULL;
	t_fd_buffer			*current_fd;
	t_string			newline;
	ssize_t				byte_read;

	current_fd = _setup_fd_buffer(fd, &fd_list);
	newline = (t_string){NULL, 0, 0};
	while (1)
	{
		byte_read = ft_getc(current_fd);
		if (byte_read == COULD_NOT_READ)
		{
			if (newline.str)
				free(newline.str);
			return (NULL);
		}
		ft_putc(&newline, byte_read);
		if (byte_read == '\n')
			break ;
	}
	if (newline.len > 0)
		ft_putc(&newline, '\0');
	return (newline.str);
}
