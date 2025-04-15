/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_visibility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:52:00 by tkomai           #+#    #+#             */
/*   Updated: 2025/04/15 15:52:00 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	is_line_visible(t_point p0, t_point p1)
{
	if ((p0.x < 0 && p1.x < 0)
		|| (p0.x >= WIDTH && p1.x >= WIDTH)
		|| (p0.y < 0 && p1.y < 0)
		|| (p0.y >= HEIGHT && p1.y >= HEIGHT))
		return (0);
	return (1);
}

void	init_draw_line(t_point *p, t_point p0, int params[5])
{
	params[0] = 0;
	params[1] = 0;
	params[2] = 0;
	params[3] = 0;
	params[4] = 0;
	p->x = 0;
	p->y = 0;
	p->z = 0;
	p->color = 0;
	p->x = p0.x;
	p->y = p0.y;
	p->z = p0.z;
	p->color = p0.color;
}

void	process_pixel(t_env *env, t_point p, t_line_data *line)
{
	if (p.x >= 0 && p.x < WIDTH && p.y >= 0 && p.y < HEIGHT)
		draw_pixel(env, p, line);
	else
		line->current_step++;
}
