/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 06:08:00 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/10 14:33:58 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	parse_line(char *line, int *row_data, int cols)
{
	char	**tokens;
	int		i;
	int		result;

	tokens = ft_split(line, ' ');
	if (!tokens)
		return (0);
	i = 0;
	result = 1;
	while (tokens[i] && tokens[i][0] != '\n')
	{
		if (i >= cols)
		{
			free_tokens(tokens);
			return (0);
		}
		row_data[i] = ft_atoi(tokens[i]);
		i++;
	}
	free_tokens(tokens);
	return (result);
}

int	has_digit(char *line)
{
	return (ft_strchr(line, '0') || ft_strchr(line, '1')
		|| ft_strchr(line, '2') || ft_strchr(line, '3')
		|| ft_strchr(line, '4') || ft_strchr(line, '5')
		|| ft_strchr(line, '6') || ft_strchr(line, '7')
		|| ft_strchr(line, '8') || ft_strchr(line, '9'));
}

void	free_tokens(char **tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

// int	parse_line(char *line, int *row_data, int cols)
// {
// 	char	**tokens;
// 	int		i;
// 	int		result;

// 	tokens = ft_split(line, ' ');
// 	if (!tokens)
// 		return (0);
// 	i = 0;
// 	result = 1;
// 	while (tokens[i] && tokens[i][0] != '\n')
// 	{
// 		if (i >= cols)
// 		{
// 			free_tokens(tokens);
// 			return (0);
// 		}
// 		row_data[i] = ft_atoi(tokens[i]);
// 		i++;
// 	}
// 	if (i != cols)
// 	{
// 		free_tokens(tokens);
// 		return (0);
// 	}
// 	free_tokens(tokens);
// 	return (result);
// }