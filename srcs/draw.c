/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:28:27 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/10 15:38:36 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	draw_right_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		z_right;
	int		coords[3];

	if (x < env->map->cols - 1)
	{
		z_right = env->map->data[y][x + 1];
		p0.z = z;
		p0.color = get_color_from_z(z);
		p1.z = z_right;
		p1.color = get_color_from_z(z_right);
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
		isometric(coords, env, &p0.x, &p0.y);
		coords[0] = x + 1;
		coords[2] = z_right;
		isometric(coords, env, &p1.x, &p1.y);
		draw_gradient_line(env, p0, p1);
	}
}

void	draw_down_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		z_down;
	int		coords[3];

	if (y < env->map->rows - 1)
	{
		z_down = env->map->data[y + 1][x];
		p0.z = z;
		p0.color = get_color_from_z(z);
		p1.z = z_down;
		p1.color = get_color_from_z(z_down);
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
		isometric(coords, env, &p0.x, &p0.y);
		coords[1] = y + 1;
		coords[2] = z_down;
		isometric(coords, env, &p1.x, &p1.y);
		draw_gradient_line(env, p0, p1);
	}
}

void	draw_map(t_env *env)
{
	int	x;
	int	y;
	int	z;

	mlx_clear_window(env->mlx, env->win);
	y = 0;
	while (y < env->map->rows)
	{
		x = 0;
		while (x < env->map->cols)
		{
			z = env->map->data[y][x];
			draw_right_connection(env, x, y, z);
			draw_down_connection(env, x, y, z);
			x++;
		}
		y++;
	}
}
