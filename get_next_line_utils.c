/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/12/07 18:09:17 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief srcをdstに文字数srcsizeまでコピーします 
 *
 * @param [out] dst		: コピー先の文字列領域
 * @param [in]	src 	: コピーする文字列
 * @param [in]	srcsize	: コピーサイズ
 * @return char* 		: dstの先頭ポインタ
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
 * @brief メモリ領域bにサイズlenまでcの内容で埋めます
 *
 * @param b			: セットするメモリ領域
 * @param c			: セットする文字(255以上の上位ビットは無視されます)
 * @param len		: セットするサイズ
 * @return void*	: bのアドレス
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
 * @brief count * sizeのメモリ領域を0埋めした状態で確保します
 * 
 * @param count		: 確保するメモリ領域の個数 
 * @param size		: メモリ領域のサイズ
 * @return void*	: 確保したメモリ領域の先頭ポインタ 
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
 * @brief lineの中の文字列を解放してNULLをセットします。
 * 
 * @param line		: 行の情報を管理する構造体
 * @return void*	: NULLを返します
 */
void	*gnl_line_free(t_string *line)
{
	if (line->str)
	{
		free(line->str);
		line->str = NULL;
	}
	return (NULL);
}

/**
 * @brief putcとgetcの状態からgnlの状態を設定します
 *
 * @param [out]	status	: 状態管理用の構造体
 * @return t_sts*		: gnlの状態適用後のstatus
 * @note	GNL_READ	: 行読み取り中
 * @note	GNL_EOF		: EOFに達した
 * @note	GNL_ERR		: 処理中にエラーが発生
 */
t_sts	*set_sts(t_sts *status)
{
	if (status->getc_sts == GETC_OTHER && status->putc_sts == PUTC_OK)
		status->gnl_sts = GNL_READ;
	else if (status->getc_sts == GETC_LF && status->putc_sts == PUTC_OK)
		status->gnl_sts = GNL_LF;
	else if (status->getc_sts == GETC_EOF && status->putc_sts == PUTC_OK)
		status->gnl_sts = GNL_EOF;
	else
		status->gnl_sts = GNL_ERR;
	return (status);
}
