/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 10:21:00 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/26 18:21:11 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// static t_fd_exist	_is_fd_exist(int fd, t_fd_info *fd_data);
static t_status	_fd_info_init(int fd, t_fd_info **fd_info_list);
static t_status	_get_fd_info(int fd, t_fd_info *base, t_fd_info **node);

// /**
//  * @brief fdの構造体が存在するかチェックします
//  *
//  * @param fd 			: 存在するか確認したいファイルディスクリプタ
//  * @param fd_data		: ファイルディスクリプタの構造体
//  * @retval FD_EXIST		: 構造体が存在します(実質1)
//  * @retval FD_NOT_EXIST	: 構造体が存在しません(実質0)
//  *
//  */
// static t_fd_exist	_is_fd_exist(int fd, t_fd_info *fd_data)
// {
// 	t_fd_info	*now_node;

// 	now_node = fd_data;
// 	while (now_node)
// 	{
// 		if (now_node->fd == fd)
// 			return (FD_EXIST);
// 		now_node = now_node->next;
// 	}
// 	return (FD_NOT_EXIST);
// }

/**
 * @brief fdの領域を初期化します。存在する場合はlineに関する情報だけ初期化します。
 *
 * @param fd 			: ファイルディスクリプタ
 * @param fd_info		: ファイルディスクリプタで管理する情報の構造体
 * @retval e_status OK	: 正常終了
 * @retval e_status NG	: メモリ割り当てに失敗した
 */
static t_status	_fd_info_init(int fd, t_fd_info **fd_info_list)
{
	t_fd_info	*new_info;

	if (_get_fd_info(fd, *fd_info_list, &new_info) == STATUS_OK)
		return (STATUS_OK);
	new_info = malloc(sizeof(t_fd_info));
	if (!new_info)
		return (STATUS_NG);
	*new_info = (t_fd_info){.fd = fd, .buf = NULL, .buf_len = 0, .next = *fd_info_list};
	new_info->buf = malloc(BUFFER_SIZE);
	if (!new_info->buf)
	{
		free(new_info);
		return (STATUS_NG);
	}
	*fd_info_list = new_info;
	return (STATUS_OK);
}

/**
 * @brief baseにあるfdと一致するノードをnodeに格納します
 *
 * @param [in] fd 		: ファイルディスクリプタ
 * @param [in] base		: ファイルディスクリプタ情報の連結リスト
 * @param [out] node 	: 一致したノードを格納する変数
 * @retval STATUS_OK	: fdの構造体が見つかった
 * @retval STATUS_NG	: fdの構造体が見つからなかった
 */
static t_status	_get_fd_info(int fd, t_fd_info *base, t_fd_info **node)
{
	t_fd_info	*check;

	check = base;
	while (check)
	{
		if (check->fd == fd)
		{
			*node = check;
			return (STATUS_OK);
		}
		check = check->next;
	}
	return (STATUS_NG);
}

/**
 * @brief	指定したファイルディスクリプタの構造体を削除します
 *
 * @param [in]	fd		: ファイルディスクリプタ
 * @param [out]	fd_list	: fd構造体のリスト
 * @note
 * 	内部変数currentで二重ポインタを使っているのは
 * 	通常処理が変わる単一リンクリストの削除処理を
 *  一貫した処理で行える様にするため
 */
static void	*_remove_fd_node(int fd, t_fd_info **fd_list)
{
	t_fd_info	**current;
	t_fd_info	*to_free;

	current = fd_list;
	while (*current)
	{
		if ((*current)->fd == fd)
		{
			to_free = *current;
			*current = (*current)->next;
			if (to_free->buf)
			{
				free(to_free->buf);
				to_free->buf = NULL;
			}
			free(to_free);
			break ;
		}
		current = &(*current)->next;
	}
	return (NULL);
}

/**
 * @brief fdから取得したテキストを改行文字を含んで取得します
 * @param [in] fd	: ファイルディスクリプタ
 * @retval char* 	: 読み込んだ1行の文字列(\n含む)
 * @retval NULL		: 中身が無くて読み込めなかったかエラーが起きた
 */
char	*get_next_line(int fd)
{
	static t_fd_info	*fd_info_list = NULL;
	t_fd_info			*now_fd_info;
	t_line_info			line_info;

	now_fd_info = NULL;
	line_info = (t_line_info){.capa = 0, .len = 0, .str = NULL};
	if (_fd_info_init(fd, &fd_info_list) == STATUS_NG)
		return (NULL);
	if (_get_fd_info(fd, fd_info_list, &now_fd_info) == STATUS_NG)
		return (_remove_fd_node(fd, &fd_info_list));
	while (1)
	{
		if (ft_getbuf(now_fd_info) == STATUS_NG)
			return (_remove_fd_node(fd, &fd_info_list));
		if (ft_putline(&line_info, now_fd_info) == STATUS_NG)
			return (_remove_fd_node(fd, &fd_info_list));
		if (ft_contain_linebreak(line_info.str) == STATUS_OK)
			break ;
	}
	return (line_info.str);
}
