/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 13:37:28 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/21 13:58:31 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx_linux/mlx.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

// keycodes
# define ESC 65307
# define D 100
# define R 114
# define X 120
# define Y 121
# define Z 122
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 61
# define MIN 45

// mouse buttons
# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

// events
# define KEY_PRESS 2
# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define MOUSE_MOVE 6
# define EXIT 17

// terminal colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define DEFAULT "\033[0m"

// default values
# define DEFAULT_X_ROTATION 2.12
# define DEFAULT_Y_ROTATION -0.1
# define DEFAULT_Z_ROTATION 0.75
# define DEFAULT_BOX_X 1000
# define DEFAULT_BOX_Y 700
# define DEFAULT_BOX_Z 200
# define ROTATION_EFFECT 0.05
# define ZOOM_IN_EFFECT 1.05
# define ZOOM_OUT_EFFECT 0.95

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef struct s_line_index
{
	int	il1;
	int	il2;
}	t_line_index;

typedef struct s_map
{
	int				width;
	int				height;
	int				top;
	int				bottom;
	int				line_count;
	int				*map;
	int				*colors;
	float			x_rotation;
	float			y_rotation;
	float			z_rotation;
	float			offset_x;
	float			offset_y;
	t_point			dimensions;
	t_line_index	*lines;
}	t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_matrix
{
	int		height;
	int		width;
	float	matrix[16];
}	t_matrix;

typedef struct s_line
{
	t_point	start;
	t_point	end;
	int		start_color;
	int		end_color;
}	t_line;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	int		screen_width;
	int		screen_height;
	int		left_mouse_pressed;
	int		right_mouse_pressed;
	int		mouse_x;
	int		mouse_y;
}	t_vars;

t_map		*fetch_map(char *filename);

t_point		*get_point_list(t_map *map);

t_matrix	projection_matrix(void);
t_matrix	z_rotation_matrix(float rotation);
t_matrix	y_rotation_matrix(float rotation);
t_matrix	x_rotation_matrix(float rotation);

t_point		calculate_map_dimensions(t_map *map);
t_point		calculate_projection(t_point point, t_map *map, \
				int recalculate_matrix);

int			fetch_lines(t_map *map);
int			render_frame(t_vars *vars);
int			exit_program(t_vars *vars);
int			main(int argc, char **argv);
int			handle_keypress(int keycode, t_vars *vars);
int			handle_mouse_drag(int x, int y, t_vars *vars);
int			mouse_up(int button, int x, int y, t_vars *vars);
int			mouse_down(int button, int x, int y, t_vars *vars);

#endif