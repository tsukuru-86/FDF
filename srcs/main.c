/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 08:31:34 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/12 22:51:00 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

void	init_env(t_env *env)
{
	env->angle = 0;
	env->angle_x = 0;
	env->offset_x = WIDTH / 2;
	env->offset_y = HEIGHT / 2;
	env->scale = SCALE;
}

/**
 * main(): プログラムのエントリーポイント
 * 引数で指定された .fdf ファイルから地形データを読み込み、
 * MiniLibX でウィンドウを生成し、初期の描画とイベントハンドラの登録を行う。
 */

int	main(int argc, char *argv[])
{
	t_env	env;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map_file>\n", 24);
		return (1);
	}
	env.map = parse_map(argv[1]);
	if (!env.map)
	{
		write(2, "Error reading the map\n", 22);
		return (1);
	}
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "FDF");
	env.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.addr = mlx_get_data_addr(env.img, &env.bits_per_pixel, &env.line_length, &env.endian);
	init_env(&env);
	mlx_hook(env.win, 2, 1L << 0, key_hook, &env);
	mlx_hook(env.win, 17, 0, close_window, &env);
	draw_map(&env);
	mlx_loop(env.mlx);
	return (0);
}
