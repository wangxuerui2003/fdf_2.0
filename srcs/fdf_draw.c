/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:14 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/19 22:41:24 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_background(t_fdf *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->data_addr);
	i = -1;
	while (++i < HEIGHT * WIDTH)
	{
		if ((i / WIDTH < MENU_SIZE) && (i % WIDTH < MENU_SIZE))
			image[i] = MENU_BACKGROUND;
		else
			image[i] = BACKGROUND;
	}
}

static void	draw_pixel(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if ((x >= MENU_SIZE || y >= MENU_SIZE) && x < WIDTH && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

static void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_point	delta;
	t_point	direction;
	t_point	current;
	int		error[2];

	current = p1;
	delta.x = p1.x - p2.x;
	delta.y = p1.y - p2.y;
	direction.x = -1 + (2 * (delta.x < 0));
	direction.y = -1 + (2 * (delta.y < 0));
	error[0] = abs(delta.x) - abs(delta.y);
	while ((p1.x > 0 && p2.x > 0) && (current.x != p2.x || current.y != p2.y))
	{
		draw_pixel(fdf, current.x, current.y, get_color(current, p1, p2, delta));
		error[1] = error[0] * 2;
		if (error[1] > -abs(delta.y))
		{
			error[0] -= abs(delta.y);
			current.x += direction.x;
		}
		if (error[1] < abs(delta.x))
		{
			error[0] += abs(delta.x);
			current.y += direction.y;
		}
	}
}

void	fdf_draw(t_fdf *fdf)
{
	int		x;
	int		y;

	draw_background(fdf);
	y = -1;
	while (++y < fdf->map->height)
	{
		x = -1;
		while (++x < fdf->map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(fdf, project(new_point(x, y, fdf->map), fdf),
					project(new_point(x + 1, y, fdf->map), fdf));
			if (y != fdf->map->height - 1)
				draw_line(fdf, project(new_point(x, y, fdf->map), fdf),
					project(new_point(x, y + 1, fdf->map), fdf));
		}
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	fdf_print_manual(fdf);
}
