/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 07:40:34 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/13 08:18:54 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

/**
 * マップの中心座標を計算
 */
void	get_center(t_env *env, double *center_x, double *center_y)
{
	*center_x = (double)(env->map->cols - 1) / 2.0;
	*center_y = (double)(env->map->rows - 1) / 2.0;
}

void	calculate_iso_coords(double coords[3], t_env *env,
	int *iso_x, int *iso_y)
{
	double	iso_angle;

	/* 初期化を確実に行う */
	if (iso_x == NULL || iso_y == NULL)
		return;
		
	iso_angle = 30.0 * (M_PI / 180.0);
	*iso_x = round((coords[0] - coords[1]) * cos(iso_angle) * env->scale
			+ env->offset_x);
	*iso_y = round(((coords[0] + coords[1]) * sin(iso_angle) - coords[2])
			* env->scale + env->offset_y);
}

/**
 * isometric(): 3D座標 (x, y, z) をアイソメトリック投影し、直感的な回転を適用して
 * 画面上の座標 (iso_x, iso_y) に変換する。
 */
void	isometric(int coords[3], t_env *env, int *iso_x, int *iso_y)
{
	double	center_x;
	double	center_y;
	double	rotated_coords[3];

	/* 初期化を確実に行う */
	if (iso_x == NULL || iso_y == NULL)
		return;
		
	/* 全ての要素を初期化 */
	rotated_coords[0] = 0.0;
	rotated_coords[1] = 0.0;
	rotated_coords[2] = 0.0;
	
	get_center(env, &center_x, &center_y);
	rotated_coords[0] = coords[0] - center_x;
	rotated_coords[1] = coords[1] - center_y;
	rotated_coords[2] = (double)coords[2] * ALT;
	rotate_point(&rotated_coords[0], &rotated_coords[1],
		&rotated_coords[2], env);
	calculate_iso_coords(rotated_coords, env, iso_x, iso_y);
}
