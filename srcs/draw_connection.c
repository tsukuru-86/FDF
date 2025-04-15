/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:48:00 by tkomai           #+#    #+#             */
/*   Updated: 2025/04/15 15:48:00 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	draw_right_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		coords[3];

	init_points(&p0, &p1);
	if (x < env->map->cols - 1)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
		set_right_points(env, &p0, &p1, coords);
		if (is_far_outside(p0.x, p0.y) && is_far_outside(p1.x, p1.y))
			return ;
		draw_gradient_line(env, p0, p1);
	}
}

void	draw_down_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		coords[3];

	init_points(&p0, &p1);
	if (y < env->map->rows - 1)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
		set_down_points(env, &p0, &p1, coords);
		if (is_far_outside(p0.x, p0.y) && is_far_outside(p1.x, p1.y))
			return ;
		draw_gradient_line(env, p0, p1);
	}
}
