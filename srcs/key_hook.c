/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:53:40 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/12 22:05:20 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	close_window(t_env *env)
{
	void	*mlx_ptr;

	mlx_ptr = env->mlx;
	mlx_destroy_window(env->mlx, env->win);
	free_map(env->map);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	exit(0);
}

static void	handle_transform_keys(int keycode, t_env *env)
{
	if (keycode == 97)
		env->angle -= 5;
	else if (keycode == 100)
		env->angle += 5;
	else if (keycode == 119)
		env->angle_x += 5;
	else if (keycode == 115)
		env->angle_x -= 5;
	else if (keycode == 65362)
		env->offset_y -= 10;
	else if (keycode == 65364)
		env->offset_y += 10;
	else if (keycode == 65361)
		env->offset_x -= 10;
	else if (keycode == 65363)
		env->offset_x += 10;
	else if (keycode == 65451)
		env->scale *= 1.1;
	else if (keycode == 65453)
		env->scale *= 0.9;
}

int	key_hook(int keycode, t_env *env)
{
	if (keycode == 65307)
	{
		close_window(env);
	}
	handle_transform_keys(keycode, env);
	draw_map(env);
	return (0);
}
