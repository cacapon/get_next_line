/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 13:30:24 by ttsubo           ###   ########.fr       */
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
	t_fd_buffer	*new_node;

	new_node = malloc(sizeof(t_fd_buffer));
	if (!new_node)
		return (NULL);
	*new_node = (t_fd_buffer){.fd = fd, .buffer = NULL, .next = NULL};
	return (new_node);
}

/**
 * @brief 先頭に新しいノードを追加します
 *
 * @param head
 * @param new_node
 */
void	add_fd_node(t_fd_buffer **head, t_fd_buffer *new_node)
{
	if (!head || !new_node)
		return ;
	new_node->next = *head;
	*head = new_node;
}

/**
 * @brief 指定したfdのノードを削除します。
 *
 * @param head
 * @param fd
 */
void	delete_fd_node(t_fd_buffer **head, int fd)
{
	t_fd_buffer	*current;
	t_fd_buffer	*prev;

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
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/**
 * @brief 引数fdのノードを返します。
 *
 * @param head
 * @param fd
 * @return t_fd_buffer*
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
