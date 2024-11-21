/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/21 13:22:11 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief 渡されたfdのfd_state構造体を取得します(無ければ新規作成)
 *
 * @param [out]	fd_list	: fd_stateのリスト
 * @param [in]	fd		: ファイルディスクプリタ
 * @return t_fd_state*	: 指定したfdの構造体を返します
 */
t_fd_state	*get_fd_node(t_fd_state **fd_list, int fd)
{
	t_fd_state	*current;
	t_fd_state	*new_node;

	current = *fd_list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	new_node = malloc(sizeof(t_fd_state));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->n = 0;
	new_node->bufp = NULL;
	new_node->next = *fd_list;
	*fd_list = new_node;
	return (new_node);
}

/**
 * @brief	指定したファイルディスクリプタの構造体を削除します
 *
 * @param [out]	fd_state_list	: fd構造体のリスト
 * @param [in]	fd				: ファイルディスクリプタ
 * @note
 * 	内部変数currentで二重ポインタを使っているのは
 * 	通常処理が変わる単一リンクリストの削除処理を
 *  一貫した処理で行える様にするため
 */
void	remove_fd_node(t_fd_state **fd_list, int fd)
{
	t_fd_state	**current;
	t_fd_state	*to_free;

	current = fd_list;
	while (*current)
	{
		if ((*current)->fd == fd)
		{
			to_free = *current;
			*current = (*current)->next;
			free(to_free);
			return ;
		}
		current = &(*current)->next;
	}
}

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

/**
 * @brief Returns one character read from fd for BUFFER_SIZE.
 * @details
 * 	The remaining characters are retained.
 * @param [in] fd 			: file descriptor
 * @retval int				: One character read
 * @retval COULD_NOT_READ	:	Couldn't read it
 */
int	ft_getc(t_fd_state *state)
{
	if (!state)
		return (COULD_NOT_READ);
	if (state->n == 0)
	{
		state->n = read(state->fd, state->buf, BUFFER_SIZE);
		if (state->n <= 0)
			return (COULD_NOT_READ);
		state->bufp = state->buf;
	}
	state->n--;
	return ((unsigned char)*state->bufp++);
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
