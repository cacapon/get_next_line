/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:41 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/30 13:17:02 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief create new fd node
 *
 * @param fd			: file descriptor
 * @retval t_fd_buf*	: fd_buf structures
 */
static t_fd_buf	*_new_fd_node(int fd)
{
	size_t		ui;
	t_fd_buf	*new_node;

	new_node = malloc(sizeof(t_fd_buf));
	if (!new_node)
		return (NULL);
	*new_node = (t_fd_buf){.fd = fd, .next = NULL};
	new_node->buf = malloc(BUFFER_SIZE * sizeof(char));
	if (!new_node->buf)
	{
		free(new_node);
		return (NULL);
	}
	ui = 0;
	while (ui < BUFFER_SIZE)
		new_node->buf[ui++] = '\0';
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
static int	_add_fd_node(t_fd_buf **head, t_fd_buf *new_node)
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
int	delete_fd_node(t_fd_buf **head, int fd)
{
	t_fd_buf	*current;
	t_fd_buf	*prev;

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
			if (current->buf)
				free(current->buf);
			free(current);
			return (GNL_OK);
		}
		prev = current;
		current = current->next;
	}
	return (GNL_NG);
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

/**
 * @brief Set up fd buf
 *
 * @param fd 			: file descripter
 * @param fd_list		: List of fd_buf structures
 * @return t_fd_buf*	: Returns the structure of fd_buf specified by the fd
 */
t_fd_buf	*setup_fd_buf(int fd, t_fd_buf **fd_list)
{
	t_fd_buf	*current_fd;
	t_fd_buf	*head;

	if (read(fd, NULL, 0) == -1 && errno == EBADF)
		return (NULL);
	head = *fd_list;
	while (head && head->fd != fd)
		head = head->next;
	current_fd = head;
	if (!current_fd)
	{
		current_fd = _new_fd_node(fd);
		if (!current_fd)
			return (NULL);
		if (_add_fd_node(fd_list, current_fd) == GNL_NG)
		{
			delete_fd_node(fd_list, fd);
			return (NULL);
		}
	}
	return (current_fd);
}
