/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 15:28:45 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief create new fd node
 * 
 * @param fd			: file descriptor
 * @retval t_fd_buffer*	: fd_buffer structures
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
 * @brief Add a new node at the beginning
 *
 * @param head 		: First pointer to fd structure list
 * @param new_node	:Pointer to node to be added
 * @retval GNL_OK	: node creation succeeded
 * @retval GNL_NG	: Node creation failure
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
 * @brief Delete a node in the specified fd.
 *
 * @param head : head of list of file descriptor nodes
 * @param fd : file descriptor to search
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
			free(current);
			return (GNL_OK);
		}
		prev = current;
		current = current->next;
	}
	return (GNL_NG);
}

/**
 * @brief Searches for a node in argument fd and returns a pointer to it.
 *
 * @param head : head of the list of file descriptor nodes
 * @param fd : file descriptor to search
 * @retval t_fd_buffer* : pointer to the found node (success)
 * @retval NULL : if node not found
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
