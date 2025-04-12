/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:51:20 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/12 22:51:23 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"
#include <stdlib.h>

void	init_line_params(int *params, t_point p0, t_point p1)
{
	params[0] = abs(p1.x - p0.x);
	params[1] = abs(p1.y - p0.y);
	if (p0.x < p1.x)
		params[2] = 1;
	else
		params[2] = -1;
	if (p0.y < p1.y)
		params[3] = 1;
	else
		params[3] = -1;
	params[4] = params[0] - params[1];
}

void	update_position(int params[5], t_point *p)
{
	int	e2;

	e2 = 2 * params[4];
	if (e2 > -params[1])
	{
		params[4] -= params[1];
		p->x += params[2];
	}
	if (e2 < params[0])
	{
		params[4] += params[0];
		p->y += params[3];
	}
}

void	setup_line(t_point p0, t_point p1, int params[5], t_line_data *line)
{
	init_line_params(params, p0, p1);
	line->color_start = get_color_from_z(p0.z);
	line->color_end = get_color_from_z(p1.z);
	if (params[0] > params[1])
		line->steps = params[0];
	else
		line->steps = params[1];
	line->current_step = 0;
}

void	draw_pixel(t_env *env, t_point p, t_line_data *line)
{
	double	t;
	int		color;

	if (line->steps == 0)
		t = 0.0;
	else
		t = (double)line->current_step / line->steps;
	color = interpolate_color(line->color_start, line->color_end, t);
	mlx_pixel_put(env->mlx, env->win, p.x, p.y, color);
	line->current_step++;
}

void	draw_gradient_line(t_env *env, t_point p0, t_point p1)
{
	int			params[5];
	t_line_data	line;
	t_point		p;

	p = p0;
	setup_line(p0, p1, params, &line);
	while (1)
	{
		draw_pixel(env, p, &line);
		if (p.x == p1.x && p.y == p1.y)
			break ;
		update_position(params, &p);
	}
}
