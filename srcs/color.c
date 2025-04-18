/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkomai <tkomai@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 08:42:23 by tsukuru           #+#    #+#             */
/*   Updated: 2025/04/15 17:05:32 by tkomai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/FDF.h"

int	get_color_from_z(int z)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	t = (double)z / 10.0;
	if (t > 1)
		t = 1;
	if (t < 0)
		t = 0;
	red = (int)(255 * t);
	green = (int)(255 * (1 - t));
	blue = 0;
	return ((red << 16) | (green << 8) | blue);
}

void	extract_colors(int color, int *r, int *g, int *b)
{
	*r = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*b = color & 0xFF;
}

int	combine_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	interpolate_color(int color_start, int color_end, double t)
{
	int	rgb_start[3];
	int	rgb_end[3];
	int	rgb_result[3];

	extract_colors(color_start, &rgb_start[0], &rgb_start[1], &rgb_start[2]);
	extract_colors(color_end, &rgb_end[0], &rgb_end[1], &rgb_end[2]);
	rgb_result[0] = (int)(rgb_start[0] + (rgb_end[0] - rgb_start[0]) * t);
	rgb_result[1] = (int)(rgb_start[1] + (rgb_end[1] - rgb_start[1]) * t);
	rgb_result[2] = (int)(rgb_start[2] + (rgb_end[2] - rgb_start[2]) * t);
	return (combine_rgb(rgb_result[0], rgb_result[1], rgb_result[2]));
}
