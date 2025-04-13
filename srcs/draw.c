/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:28:27 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/13 08:25:10 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

/* 点が画面から大きく離れているかチェック（マージン付き） */
int	is_far_outside(int x, int y)
{
	const int margin = 100; /* 画面外のマージン */
	
	return (x < -margin || x >= WIDTH + margin || 
			y < -margin || y >= HEIGHT + margin);
}

void	draw_right_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		z_right;
	int		coords[3];

	/* 構造体を完全に初期化 */
	p0.x = 0;
	p0.y = 0;
	p0.z = 0;
	p0.color = 0;
	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	p1.color = 0;

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
		
		/* 最初の点が画面から大きく離れている場合はスキップ */
		if (is_far_outside(p0.x, p0.y))
			return;
			
		coords[0] = x + 1;
		coords[1] = y;  /* y座標を明示的に設定 */
		coords[2] = z_right;
		isometric(coords, env, &p1.x, &p1.y);
		
		/* 両方の点が画面から大きく離れている場合はスキップ */
		if (is_far_outside(p0.x, p0.y) && is_far_outside(p1.x, p1.y))
			return;
			
		draw_gradient_line(env, p0, p1);
	}
}

void	draw_down_connection(t_env *env, int x, int y, int z)
{
	t_point	p0;
	t_point	p1;
	int		z_down;
	int		coords[3];

	/* 構造体を完全に初期化 */
	p0.x = 0;
	p0.y = 0;
	p0.z = 0;
	p0.color = 0;
	p1.x = 0;
	p1.y = 0;
	p1.z = 0;
	p1.color = 0;

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
		
		/* 最初の点が画面から大きく離れている場合はスキップ */
		if (is_far_outside(p0.x, p0.y))
			return;
			
		coords[0] = x;  /* x座標を明示的に設定 */
		coords[1] = y + 1;
		coords[2] = z_down;
		isometric(coords, env, &p1.x, &p1.y);
		
		/* 両方の点が画面から大きく離れている場合はスキップ */
		if (is_far_outside(p0.x, p0.y) && is_far_outside(p1.x, p1.y))
			return;
			
		draw_gradient_line(env, p0, p1);
	}
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

/* マップの特定の領域が画面内に表示される可能性があるかチェック */
int	is_region_visible(t_env *env, int start_x, int start_y, int size)
{
	t_point	corner;
	int		coords[3];
	int		i, j;
	int		margin = 200; /* 余裕を持たせる */
	int		end_x, end_y;
	
	/* 領域の四隅をチェック */
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			coords[0] = start_x + (i * size);
			coords[1] = start_y + (j * size);
			
			/* 境界チェック */
			end_y = start_y + (j * size);
			if (end_y >= env->map->rows)
				end_y = env->map->rows - 1;
				
			end_x = start_x + (i * size);
			if (end_x >= env->map->cols)
				end_x = env->map->cols - 1;
				
			coords[2] = env->map->data[end_y][end_x];
			
			corner.x = 0;
			corner.y = 0;
			isometric(coords, env, &corner.x, &corner.y);
			
			/* 一つでも画面内（またはマージン内）なら描画する必要がある */
			if (corner.x >= -margin && corner.x < WIDTH + margin && 
				corner.y >= -margin && corner.y < HEIGHT + margin)
				return (1);
		}
	}
	return (0);
}

void	draw_map(t_env *env)
{
	int x;
	int y;
	int z;
	int region_size = 8; /* 分割サイズ - 調整可能 */

	clear_image(env);
	
	/* マップを領域に分割して処理 */
	for (y = 0; y < env->map->rows; y += region_size)
	{
		for (x = 0; x < env->map->cols; x += region_size)
		{
			/* この領域が画面内に表示される可能性があるかチェック */
			if (is_region_visible(env, x, y, region_size))
			{
				/* 領域内の各点を処理 */
				int end_y = y + region_size;
				if (end_y > env->map->rows)
					end_y = env->map->rows;
					
				int end_x = x + region_size;
				if (end_x > env->map->cols)
					end_x = env->map->cols;
					
				int i, j;
				
				for (i = y; i < end_y; i++)
				{
					for (j = x; j < end_x; j++)
					{
						z = env->map->data[i][j];
						draw_right_connection(env, j, i, z);
						draw_down_connection(env, j, i, z);
					}
				}
			}
		}
	}
	
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
