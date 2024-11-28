/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 12:12:24 by ttsubo           ###   ########.fr       */
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
int	ft_getc(int fd)
{
	static t_fd_state	state[MAX_FD];

	if (fd < 0)
		return (COULD_NOT_READ);
	if (state[fd].n == 0)
	{
		state[fd].n = read(fd, state[fd].buf, sizeof(state[fd].buf));
		if (state[fd].n <= 0)
			return (COULD_NOT_READ);
		state[fd].bufp = state[fd].buf;
	}
	state[fd].n--;
	return ((unsigned char)*state[fd].bufp++);
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
