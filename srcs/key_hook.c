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
	/* mlx_destroy_display(mlx_ptr); */ /* Linux用の関数 - Mac版では使用しない */
	free(mlx_ptr);
	exit(0);
}

static void	handle_transform_keys(int keycode, t_env *env)
{
	if (keycode == 0 || keycode == 97)
		env->angle -= 5;
	else if (keycode == 2 || keycode == 100)
		env->angle += 5;
	else if (keycode == 13 || keycode == 119)
		env->angle_x += 5;
	else if (keycode == 1 || keycode == 115)
		env->angle_x -= 5;
	else if (keycode == 126 || keycode == 65362)
		env->offset_y -= 10;
	else if (keycode == 125 || keycode == 65364)
		env->offset_y += 10;
	else if (keycode == 123 || keycode == 65361)
		env->offset_x -= 10;
	else if (keycode == 124 || keycode == 65363)
		env->offset_x += 10;
	else if (keycode == 24 || keycode == 69 || keycode == 65451)
		env->scale *= 1.1;
	else if (keycode == 27 || keycode == 78 || keycode == 65453)
		env->scale *= 0.9;
}

int	key_hook(int keycode, t_env *env)
{
	if (keycode == 53 || keycode == 65307)
	{
		close_window(env);
	}
	handle_transform_keys(keycode, env);
	draw_map(env);
	return (0);
}
