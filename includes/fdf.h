/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangping <wangping@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:44:03 by wxuerui           #+#    #+#             */
/*   Updated: 2022/09/19 22:42:37 by wangping         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "keys.h"
# include "colors.h"
# include "err_msg.h"

# define WIDTH		1080
# define HEIGHT		720
# define MENU_SIZE	200

/*Structures*/

/*Enable mode switch (parallel and isometric)*/
typedef enum e_mode
{
	TWO_D,
	THREE_D
}	t_mode;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_view
{
	t_mode		mode;
	int			zoom;
	double		angle_x;
	double		angle_y;
	double		angle_z;
	int			move_x;
	int			move_y;
}	t_view;

typedef struct s_map
{
	int	width;
	int	height;
	int	*coords;
	int	min;
	int	max;
}	t_map;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	t_map	*map;
	t_view	*view;

}	t_fdf;

/*Function prototypes*/
void	fdf_err_exit(char *err_msg);
void	fdf_print_manual(t_fdf *fdf);
void	fdf_hooks(t_fdf *fdf);
t_fdf	*fdf_init(char *map_file);
void	fdf_draw(t_fdf *fdf);
t_point	new_point(int x, int y, t_map *map);
t_point	project(t_point p, t_fdf *fdf);
int		close_win(t_fdf *fdf);
void	rotate_x(int *y, int *z, double alpha);
void	rotate_y(int *x, int *z, double beta);
void	rotate_z(int *x, int *y, double gamma);
int		get_point_color(t_point p, t_map *map);
int	get_color(t_point current, t_point start, t_point end, t_point delta);

#endif	/*fdf.h*/
