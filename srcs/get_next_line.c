/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 13:55:04 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/13 08:05:40 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include <fcntl.h>

/* 静的変数leftoverを解放する関数 */
void	free_gnl_leftover(void)
{
	static char	*leftover = NULL;

	if (leftover)
	{
		free(leftover);
		leftover = NULL;
	}
}

char	*ft_connect(int fd, char *buff, char *temp, char *leftover)
{
	int	read_bytes;

	read_bytes = 1;
	while ((!leftover || !ft_strchr(leftover, '\n')) && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff[read_bytes] = '\0';
		if (!leftover)
			leftover = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(leftover, buff);
			free(leftover);
			leftover = temp;
		}
		if (!leftover)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (leftover);
}

static char	*ft_read_to_leftover(int fd, char *leftover)
{
	char	*buff;
	char	*temp;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	temp = NULL;
	leftover = ft_connect(fd, buff, temp, leftover);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_read_to_leftover(fd, leftover);
	if (!leftover || leftover[0] == '\0')
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = ft_get_line(leftover);
	leftover = ft_new_leftover(leftover);
	return (line);
}
