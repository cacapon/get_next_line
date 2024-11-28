/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 13:58:51 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief ファイルディスクリプタノードを追加する
 *
 * @param fd
 * @return t_fd_buffer*
 */
t_fd_buffer	*new_fd_node(int fd)
{
	size_t		ui;
	t_fd_buffer	*new_node;

	new_node = malloc(sizeof(t_fd_buffer));
	if (!new_node)
		return (NULL);
	*new_node = (t_fd_buffer){.fd = fd, .next = NULL};
	ui = 0;
	while (ui < BUFFER_SIZE)
		new_node->buffer[ui++] = '\0';
	return (new_node);
}

/**
 * @brief 先頭に新しいノードを追加します
 *
 * @param head
 * @param new_node
 * @retval GNL_OK: ノード作成成功
 * @retval GNL_NG: ノード作成失敗
 */
t_status	add_fd_node(t_fd_buffer **head, t_fd_buffer *new_node)
{
	if (!head || !new_node)
		return (GNL_NG);
	new_node->next = *head;
	*head = new_node;
	return (GNL_OK);
}

/**
 * @brief 指定したfdのノードを削除します。
 *
 * @param head    		: ファイルディスクリプタノードのリストの先頭
 * @param fd      		: 検索対象のファイルディスクリプタ
 */
t_status	delete_fd_node(t_fd_buffer **head, int fd)
{
	t_fd_buffer	*current;
	t_fd_buffer	*prev;

	if (!head || !*head)
		return (GNL_NG);
	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->buffer);
			free(current);
			return (GNL_OK);
		}
		prev = current;
		current = current->next;
	}
	return (GNL_NG);
}

/**
 * @brief 引数fdのノードを検索し、ポインタを返します。
 *
 * @param head    		: ファイルディスクリプタノードのリストの先頭
 * @param fd      		: 検索対象のファイルディスクリプタ
 * @retval t_fd_buffer* : 見つかったノードのポインタ（成功）
 * @retval NULL         : ノードが見つからない場合
 */
t_fd_buffer	*find_fd_node(t_fd_buffer *head, int fd)
{
	while (head)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	return (NULL);
}
