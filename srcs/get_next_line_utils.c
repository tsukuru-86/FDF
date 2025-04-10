/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:45:19 by tkomai            #+#    #+#             */
/*   Updated: 2025/04/10 15:45:40 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_get_line(char *leftover)
{
	int		i;
	char	*line;

	i = 0;
	if (!leftover)
		return (NULL);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (leftover[i] && leftover[i] != '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	if (leftover[i] == '\n')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	ft_find_newline_pos(char *leftover)
{
	int	i;

	i = 0;
	if (!leftover)
		return (-1);
	while (leftover[i] && leftover[i] != '\n')
		i++;
	if (!leftover[i])
		return (-1);
	return (i);
}

char	*ft_new_leftover(char *leftover)
{
	int		i;
	int		j;
	char	*new_leftover;

	if (!leftover)
		return (NULL);
	i = ft_find_newline_pos(leftover);
	if (i == -1)
	{
		free(leftover);
		return (NULL);
	}
	new_leftover = (char *)malloc(sizeof(char) * (ft_strlen(leftover) - i + 1));
	if (!new_leftover)
	{
		free(leftover);
		return (NULL);
	}
	j = 0;
	i++;
	while (leftover[i])
		new_leftover[j++] = leftover[i++];
	new_leftover[j] = '\0';
	free(leftover);
	return (new_leftover);
}
