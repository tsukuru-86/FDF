/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:28:27 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/15 15:48:50 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	draw_map(t_env *env)
{
	int	x;
	int	y;
	int	region_size;

	region_size = 8;
	clear_image(env);
	y = 0;
	while (y < env->map->rows)
	{
		x = 0;
		while (x < env->map->cols)
		{
			if (is_region_visible(env, x, y, region_size))
				process_region(env, x, y, region_size);
			x += region_size;
		}
		y += region_size;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
