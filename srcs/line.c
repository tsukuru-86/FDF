/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:51:20 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/15 16:48:09 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"
#include <stdlib.h>

void	draw_gradient_line(t_env *env, t_point p0, t_point p1)
{
	int			params[5];
	t_line_data	line;
	t_point		p;

	if (!is_line_visible(p0, p1))
		return ;
	init_draw_line(&p, p0, params);
	setup_line(p0, p1, params, &line);
	while (1)
	{
		process_pixel(env, p, &line);
		if (p.x == p1.x && p.y == p1.y)
			break ;
		update_position(params, &p);
	}
}
