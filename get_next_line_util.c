/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/18 11:33:18 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
 * @param [in] fd : file descriptor
 * @return int: One character read
 */
int	ft_getc(int fd)
{
	static char		buf[BUFFER_SIZE];
	static char		*bufp;
	static ssize_t	n = 0;

	if (n == 0)
	{
		n = read(fd, buf, sizeof buf);
		bufp = buf;
	}
	if ((--n >= 0))
		return ((unsigned char)*bufp++);
	else
		return (EOF);
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
		tmp = malloc(str->len);
		tmp = _strncpy(tmp, str->str, str->len);
		str->capa = (str->len + 1) * 2;
		free(str->str);
		str->str = malloc(str->capa);
		if (!str->str)
			return (-1);
		str->str = _strncpy(str->str, tmp, str->len);
	}
	str->str[str->len] = c;
	str->len++;
	return (c);
}
