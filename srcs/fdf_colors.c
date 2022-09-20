/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:09 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/20 12:20:40 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_point_color(t_point p, t_map *map, t_view *view)
{
	double	percentage;

	if (view->colorscheme == DEFAULT)
		return (0xFFFFFF);
	percentage = (double)(map->max - map->coords[p.y * map->width + p.x])
		/ (double)(map->max - map->min);
	if (view->colorscheme == DARK)
		return (0xFF0000 + (percentage * 0xFF00));
	return (0x00FF00 + (percentage * 0xFF));
}

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	double	percentage;

	if (start.color == end.color || (delta.x == 0 || delta.y == 0))
		return (start.color);
	percentage = (double)abs(end.x - current.x) / (double)abs(delta.x);
	return (end.color - abs(end.color - start.color) * percentage);
}
