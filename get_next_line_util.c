/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:51:29 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/26 16:22:32 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief srcの文字列をsrcsizeまでdstにコピーします
 *
 * @param dst 		: コピー先の文字列用の領域
 * @param src 		: コピーする文字列
 * @param srcsize	: srcのサイズ
 * @return char*	: dstの先頭ポインタ
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
 * @brief 文字列に改行が含まれているかチェックします
 * 
 * @param [in] str		: 検索する文字列
 * @retval STATUS_OK	: 改行が含まれていた 
 * @retval STATUS_NG	: 改行が含まれていなかった
 */
t_status	ft_contain_linebreak(char *str)
{
	while (*str)
	{
		if(*str == '\n')
			return (STATUS_OK);
		str++;
	}
	return (STATUS_NG);
}

/**
 * @brief fd_infoのlineにbufの内容をセットします
 *
 * @param [out]	fd_info	: fdの情報を管理している構造体
 * @retval STATUS_OK	: 正常に読み込めた・読み込む必要がなかった
 * @retval STATUS_NG	: tmpのメモリ割当に失敗した
 */
t_status	ft_putline(t_fd_info *fd_info)
{
	char	*tmp;

	if (fd_info->line_capa < fd_info->line_len + fd_info->buf_len)
	{
		fd_info->line_capa = (fd_info->line_len + fd_info->buf_len) * 2;
		tmp = malloc(fd_info->line_capa);
		if (!tmp)
			return (STATUS_NG);
		tmp = _strncpy(tmp, fd_info->line, fd_info->line_len);
		free(fd_info->line);
		fd_info->line = tmp;
	}
	while (fd_info->buf_len > 0 && *(fd_info->buf) != '\0')
	{
		fd_info->line[fd_info->line_len] = *fd_info->buf++;
		fd_info->line_len++;
		fd_info->buf_len--;
		if (*(fd_info->buf) == '\n')
			break ;
	}
	return (STATUS_OK);
}

/**
 * @brief バッファがからの場合,readを使ってbufにセットします。
 *
 * @param [out]	fd_info	: fdの情報を管理している構造体
 * @retval STATUS_OK	: 正常に読み込めた・読み込む必要がなかった
 * @retval STATUS_NG	: fdから読み込めない・readしたが空だった
 */
t_status	ft_getbuf(t_fd_info *fd_info)
{
	if (!fd_info)
		return (STATUS_NG);
	if (fd_info->buf_len == 0)
	{
		fd_info->buf_len = read(fd_info->fd, fd_info->buf, BUFFER_SIZE);
		if (fd_info->buf_len <= 0)
			return (STATUS_NG);
	}
	return (STATUS_OK);
}
