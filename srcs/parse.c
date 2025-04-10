/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:47:26 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/10 14:33:35 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static int	count_cols(char *buffer)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		if (buffer[i] == ' ' && buffer[i + 1] != ' ' && buffer[i + 1] != '\n')
			spaces++;
		i++;
	}
	return (spaces + 1);
}

static int	count_rows(int fd)
{
	char	*line;
	int		row_count;

	row_count = 0;
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	while (line)
	{
		if (has_digit(line))
			row_count++;
		free(line);
		line = get_next_line(fd);
	}
	lseek(fd, 0, SEEK_SET);
	return (row_count);
}

int	count_rows_and_cols(char *filename, int *cols)
{
	int		fd;
	int		rows;
	char	buffer[4096];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
	{
		close(fd);
		return (-1);
	}
	buffer[bytes_read] = '\0';
	*cols = count_cols(buffer);
	lseek(fd, 0, SEEK_SET);
	rows = count_rows(fd);
	close(fd);
	return (rows);
}

static t_map	*cleanup_and_return(t_map *map, int fd)
{
	if (fd >= 0)
		close(fd);
	if (map)
		free_map(map);
	return (NULL);
}

t_map	*parse_map(char *filename)
{
	int		fd;
	int		rows;
	int		cols;
	t_map	*map;

	rows = count_rows_and_cols(filename, &cols);
	if (rows <= 0 || cols <= 0)
		return (NULL);
	map = allocate_map_structure(rows, cols);
	if (!map)
		return (NULL);
	if (!allocate_map_data(map))
		return (cleanup_and_return(map, -1));
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !read_map_data(map, fd))
		return (cleanup_and_return(map, fd));
	close(fd);
	return (map);
}
