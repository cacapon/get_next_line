/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/29 12:36:38 by ttsubo           ###   ########.fr       */
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
	new_node->buffer = malloc(BUFFER_SIZE * sizeof(char));
	if (!new_node->buffer)
	{
		free(new_node);
		return (NULL);
	}
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
int	add_fd_node(t_fd_buffer **head, t_fd_buffer *new_node)
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
int	delete_fd_node(t_fd_buffer **head, int fd)
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
 * @brief Set up fd buffer
 *
 * @param fd 			: file descripter
 * @param fd_list		: List of fd_buffer structures
 * @return t_fd_buffer* : Returns the structure of fd_buffer specified by the fd
 */
t_fd_buffer	*setup_fd_buffer(int fd, t_fd_buffer **fd_list)
{
	t_fd_buffer	*current_fd;
	t_fd_buffer	*head;

	if (fd < 0)
		return (NULL);
	head = *fd_list;
	while (head && head->fd != fd)
		head = head->next;
	current_fd = head;
	if (!current_fd)
	{
		current_fd = new_fd_node(fd);
		if (!current_fd)
			return (NULL);
		if (add_fd_node(fd_list, current_fd) == GNL_NG)
		{
			free(current_fd);
			return (NULL);
		}
	}
	return (current_fd);
}
