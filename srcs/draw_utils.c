/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:47:00 by tkomai           #+#    #+#             */
/*   Updated: 2025/04/15 15:47:00 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	is_far_outside(int x, int y)
{
	int	margin;

	margin = 100;
	return (x < -margin || x >= WIDTH + margin || y < -margin || y >= HEIGHT
		+ margin);
}

void	init_points(t_point *p0, t_point *p1)
{
	p0->x = 0;
	p0->y = 0;
	p0->z = 0;
	p0->color = 0;
	p1->x = 0;
	p1->y = 0;
	p1->z = 0;
	p1->color = 0;
}

void	set_right_points(t_env *env, t_point *p0, t_point *p1, int *coords)
{
	int	x;
	int	y;
	int	z;
	int	z_right;

	x = coords[0];
	y = coords[1];
	z = coords[2];
	z_right = env->map->data[y][x + 1];
	p0->z = z;
	p0->color = get_color_from_z(z);
	p1->z = z_right;
	p1->color = get_color_from_z(z_right);
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	isometric(coords, env, &p0->x, &p0->y);
	coords[0] = x + 1;
	coords[1] = y;
	coords[2] = z_right;
	isometric(coords, env, &p1->x, &p1->y);
}

void	set_down_points(t_env *env, t_point *p0, t_point *p1, int *coords)
{
	int	x;
	int	y;
	int	z;
	int	z_down;

	x = coords[0];
	y = coords[1];
	z = coords[2];
	z_down = env->map->data[y + 1][x];
	p0->z = z;
	p0->color = get_color_from_z(z);
	p1->z = z_down;
	p1->color = get_color_from_z(z_down);
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
	isometric(coords, env, &p0->x, &p0->y);
	coords[0] = x;
	coords[1] = y + 1;
	coords[2] = z_down;
	isometric(coords, env, &p1->x, &p1->y);
}

void	clear_image(t_env *env)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(env, x, y, 0);
			x++;
		}
		y++;
	}
}
