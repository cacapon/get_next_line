/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/12/07 19:07:02 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief fd_buf内にあるバッファから1文字取り出しcpにセットします
 *
 * @param [out] fd_buf	: fd_buf 構造体
 * @param [out] cp		: 文字のポインタ
 * @retval PUTC_OK		: 文字の取り出しに成功
 * @retval PUTC_ERR		: 文字取り出し中にエラーになった
 * @retval PUTC_EOF		: EOFに達した
 * @note	<pre> fd_buf != NULL (呼出し側でfd_bufを設定する必要がある)
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
	if (*cp == '\n')
		return (GETC_LF);
	else
		return (GETC_OTHER);
}

/**
 * @brief  string構造体に含まれるstrにcを追加します
 *
 * @param [out]	line	: 行情報を管理する構造体
 * @param [in]	c		: line.strに追加する文字
 * @param sts 			: getcの状態
 * @retval PUTC_OK		: lineにcを追加できた
 * @retval PUTC_ERR		: 追加する処理の途中でエラーになった
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
		tmp = gnl_calloc(line->capa, 1);
		if (!tmp)
			return (PUTC_ERR);
		gnl_strncpy(tmp, line->str, line->len);
		free(line->str);
		line->str = tmp;
	}
	line->str[line->len] = c;
	line->len++;
	return (PUTC_OK);
}

/**
 * @brief 対象のfd用バッファが未作成の場合に初期化します
 *
 * @param [out]	s_buf	: バッファ構造体のアドレス
 * @param [in]	fd		: ファイルディスクプリタ
 * @retval t_buf* 		: 初期化済みの構造体
 * @retval NULL 		: 初期化に失敗
 */
static t_buf	*_gnl_buf_init(t_buf **s_buf, int fd)
{
	if (!s_buf)
		return (NULL);
	if (!*s_buf)
	{
		*s_buf = gnl_calloc(sizeof(t_buf), 1);
		if (!*s_buf)
			return (NULL);
		(*s_buf)->buf = gnl_calloc(BUFFER_SIZE, 1);
		if (!(*s_buf)->buf)
		{
			free(*s_buf);
			*s_buf = NULL;
			return (NULL);
		}
		(*s_buf)->buf_len = 0;
		(*s_buf)->bufp = (*s_buf)->buf;
		(*s_buf)->fd = fd;
	}
	return (*s_buf);
}

/**
 * @brief 渡されたバッファ構造体メモリを解放してNULLをセットします
 *
 * @param [out]	s_buf	: メモリ解放するバッファ構造体
 */
static void	_gnl_buf_free(t_buf **s_buf)
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
 * @brief fdから改行までの文字列を改行込みで取得します 
 * @param [in] fd	: ファイルディスクリプタ
 * @retval char* 	: fdから取得した改行を含む文字列
 * @retval NULL		: 読み込み失敗エラー 
 */
char	*get_next_line(int fd)
{
	static t_buf	*buf[MAX_FD];
	t_string		newline;
	unsigned char	uc;
	t_sts			status;

	if (fd < 0 || MAX_FD <= fd)
		return (NULL);
	if (!_gnl_buf_init(&buf[fd], fd))
		return (NULL);
	newline = (t_string){.str = NULL, .len = 0, .capa = 0};
	while (1)
	{
		status.getc_sts = _ft_getc(buf[fd], &uc);
		status.putc_sts = _ft_putc(&newline, uc, status.getc_sts);
		if (set_sts(&status)->gnl_sts != GNL_READ)
			break ;
	}
	if (status.gnl_sts == GNL_LF || status.gnl_sts == GNL_EOF)
		_ft_putc(&newline, '\0', status.getc_sts);
	if (status.gnl_sts == GNL_EOF || status.gnl_sts == GNL_ERR)
		_gnl_buf_free(&buf[fd]);
	if (status.gnl_sts == GNL_ERR)
		return (gnl_line_free(&newline));
	return (newline.str);
}
