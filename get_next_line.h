/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:08:36 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/15 16:14:04 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 3
# define EOF -1
# include <unistd.h>
# include <stdlib.h>

typedef struct s_string
{
	char * str;
	size_t len;
	size_t capa;
} t_string;

int		ft_getc(int fd);
int 	ft_putc(t_string *str, char c);
char	*get_next_line(int fd);

#endif