/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 11:07:44 by ttsubo            #+#    #+#             */
/*   Updated: 2024/11/28 12:19:42 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// TODO: ft_getcが持っているfdの管理をget_next_line側で持つ
// TODO: stateの連結リスト化
// TODO: BUFをヒープで管理するようにする


/**
 * @brief fdのテキストのうち、改行までの文字列を返します。
 * @param [in] fd	: ファイルディスクリプタ
 * @retval char* 	: 読み込んだ行
 * @retval NULL		: 読めなかった・もしくはエラーだった場合
 */
char	*get_next_line(int fd)
{
	t_string	line;
	char		c;

	line = (t_string){.str = NULL, .capa = 0, .len = 0};
	if (fd < 0)
		return (NULL);
	while (1)
	{
		c = ft_getc(fd);
		if (c == COULD_NOT_READ)
			break ;
		ft_putc(&line, c);
		if (c == '\n')
			break ;
	}
	if (line.len > 0)
		ft_putc(&line, '\0');
	return (line.str);
}
