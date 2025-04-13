/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:47:26 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/13 08:08:48 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

static int	count_cols(char *line)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\n')
			spaces++;
		i++;
	}
	return (spaces + 1);
}

static int	count_rows_and_get_first_line(int fd, char **first_line)
{
	char	*line;
	int		row_count;
	int		first_line_found;

	row_count = 0;
	first_line_found = 0;
	lseek(fd, 0, SEEK_SET);
	line = get_next_line(fd);
	while (line)
	{
		if (has_digit(line))
		{
			row_count++;
			if (!first_line_found && *first_line == NULL)
			{
				*first_line = ft_strdup(line);
				first_line_found = 1;
			}
		}
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
	char	*first_line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	first_line = NULL;
	rows = count_rows_and_get_first_line(fd, &first_line);
	if (rows <= 0 || !first_line)
	{
		if (first_line)
			free(first_line);
		close(fd);
		return (-1);
	}
	*cols = count_cols(first_line);
	free(first_line);
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
