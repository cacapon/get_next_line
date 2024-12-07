/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/12/07 17:03:12 by ttsubo           ###   ########.fr       */
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
char	*gnl_strncpy(char *dst, const char *src, size_t srcsize)
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
 * @param b
 * @param c
 * @param len
 * @return void*
 */
void	*gnl_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}

/**
 * @brief 
 * 
 * @param count 
 * @param size 
 * @return void* 
 */
void	*gnl_calloc(size_t count, size_t size)
{
	void	*_block;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (size > SIZE_MAX / count)
		return (NULL);
	_block = malloc(count * size);
	if (!_block)
		return (NULL);
	gnl_memset(_block, 0, count * size);
	return (_block);
}

/**
 * @brief Set the sts object
 *
 * @param [out]	result	: state-management structure
 * @return t_sts*		: Same as argument
 */
t_sts	*set_sts(t_sts *result)
{
	if (result->getc_sts == GETC_OK && result->putc_sts == PUTC_OK)
		result->gnl_sts = GNL_READ;
	else if (result->getc_sts == GETC_EOF && result->putc_sts == PUTC_OK)
		result->gnl_sts = GNL_EOF;
	else
		result->gnl_sts = GNL_ERR;
	return (result);
}
