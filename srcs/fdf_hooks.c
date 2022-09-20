/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:45:21 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/20 11:50:28 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	zoom(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_PLUS)
		fdf->view->zoom++;
	if (key == MAIN_PAD_MINUS)
		if (fdf->view->zoom > 1)
			fdf->view->zoom--;
}

static void	move(int key, t_fdf *fdf)
{
	if (key == ARROW_UP)
		fdf->view->move_y -= HEIGHT / fdf->map->height;
	if (key == ARROW_DOWN)
		fdf->view->move_y += HEIGHT / fdf->map->height;
	if (key == ARROW_LEFT)
		fdf->view->move_x -= WIDTH / fdf->map->width;
	if (key == ARROW_RIGHT)
		fdf->view->move_x += WIDTH / fdf->map->width;
}

static void	rotate(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_2)
		fdf->view->angle_x += 0.1;
	else if (key == MAIN_PAD_8)
		fdf->view->angle_x -= 0.1;
	else if (key == MAIN_PAD_4)
		fdf->view->angle_y -= 0.1;
	else if (key == MAIN_PAD_6)
		fdf->view->angle_y += 0.1;
	else if (key == MAIN_PAD_3)
		fdf->view->angle_z += 0.1;
	else if (key == MAIN_PAD_7)
		fdf->view->angle_z -= 0.1;
}

static int	key_press(int key, t_fdf *fdf)
{
	if (key == MAIN_PAD_ESC || key == MAIN_PAD_Q)
		close_win(fdf);
	else if (key == MAIN_PAD_PLUS || key == MAIN_PAD_MINUS)
		zoom(key, fdf);
	else if (key >= ARROW_LEFT && key <= ARROW_UP)
		move(key, fdf);
	else if (key == MAIN_PAD_2 || key == MAIN_PAD_3 || key == MAIN_PAD_4
		|| key == MAIN_PAD_6 || key == MAIN_PAD_7 || key == MAIN_PAD_8)
		rotate(key, fdf);
	else if (key == MAIN_PAD_M)
	{
		if (fdf->view->mode == TWO_D)
			fdf->view->mode++;
		else
			fdf->view->mode--;
	}
	fdf_draw(fdf);
	return (0);
}

void	fdf_hooks(t_fdf *fdf)
{
	mlx_hook(fdf->win, KEY_PRESS, KEYPRESS_MASK, key_press, fdf);
	mlx_hook(fdf->win, DESTROY, LEAVEWINDOW_MASK, close_win, fdf);
}
