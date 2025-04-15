/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_region.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:47:30 by tkomai           #+#    #+#             */
/*   Updated: 2025/04/15 15:47:30 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	check_corner_visibility(t_env *env, int *coords, int margin)
{
	t_point	corner;

	corner.x = 0;
	corner.y = 0;
	isometric(coords, env, &corner.x, &corner.y);
	if (corner.x >= -margin && corner.x < WIDTH + margin
		&& corner.y >= -margin && corner.y < HEIGHT + margin)
		return (1);
	return (0);
}

int	check_region_corner(t_env *env, int x, int y, int margin)
{
	int	coords[3];
	int	safe_y;
	int	safe_x;

	safe_y = y;
	if (safe_y >= env->map->rows)
		safe_y = env->map->rows - 1;
	safe_x = x;
	if (safe_x >= env->map->cols)
		safe_x = env->map->cols - 1;
	coords[0] = x;
	coords[1] = y;
	coords[2] = env->map->data[safe_y][safe_x];
	return (check_corner_visibility(env, coords, margin));
}

int	is_region_visible(t_env *env, int start_x, int start_y, int size)
{
	int	i;
	int	j;
	int	margin;

	margin = 200;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (check_region_corner(env, start_x + (i * size),
					start_y + (j * size), margin))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	process_region_point(t_env *env, int i, int j)
{
	int	z;

	z = env->map->data[i][j];
	draw_right_connection(env, j, i, z);
	draw_down_connection(env, j, i, z);
}

void	process_region(t_env *env, int x, int y, int region_size)
{
	int	end_y;
	int	end_x;
	int	i;
	int	j;

	end_y = y + region_size;
	if (end_y > env->map->rows)
		end_y = env->map->rows;
	end_x = x + region_size;
	if (end_x > env->map->cols)
		end_x = env->map->cols;
	i = y;
	while (i < end_y)
	{
		j = x;
		while (j < end_x)
		{
			process_region_point(env, i, j);
			j++;
		}
		i++;
	}
}
