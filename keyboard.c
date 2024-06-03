/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keyboard.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 12:36:47 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 17:41:59 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	even_more_keys_to_handle(int keycode, t_vars *vars)
{
	float	max;

	max = (vars->map->dimensions.x > vars->map->dimensions.y) * \
		vars->map->dimensions.x + (vars->map->dimensions.x <= \
		vars->map->dimensions.y) * vars->map->dimensions.y;
	if (keycode == LEFT && vars->map->dimensions.x > 2)
	{
		vars->map->dimensions.x -= vars->map->dimensions.x / max;
		vars->map->dimensions.y -= vars->map->dimensions.y / max;
	}
	else if (keycode == RIGHT)
	{
		vars->map->dimensions.x += vars->map->dimensions.x / max;
		vars->map->dimensions.y += vars->map->dimensions.y / max;
	}
	return (0);
}

static int	more_keys_to_handle(int keycode, t_vars *vars)
{
	if (keycode == ESC)
		exit_program(vars);
	else if (keycode == R)
	{
		vars->map->dimensions = calculate_map_dimensions(vars->map);
		vars->map->x_rotation = DEFAULT_X_ROTATION;
		vars->map->y_rotation = DEFAULT_Y_ROTATION;
		vars->map->z_rotation = DEFAULT_Z_ROTATION;
		vars->map->offset_x = 0;
		vars->map->offset_y = 0;
	}
	else if (keycode == UP)
		vars->map->dimensions.z += 1;
	else if (keycode == DOWN)
		vars->map->dimensions.z -= 1;
	else
		return (even_more_keys_to_handle(keycode, vars));
	return (0);
}

int	handle_keypress(int keycode, t_vars *vars)
{
	float	direction;

	direction = 1 - (vars->right_mouse_pressed * 2);
	if (keycode == X)
		vars->map->x_rotation += (ROTATION_EFFECT * direction);
	else if (keycode == Y)
		vars->map->y_rotation += (ROTATION_EFFECT * direction);
	else if (keycode == Z)
		vars->map->z_rotation += (ROTATION_EFFECT * direction);
	else if (keycode == PLUS)
	{
		vars->map->dimensions.x *= ZOOM_IN_EFFECT;
		vars->map->dimensions.y *= ZOOM_IN_EFFECT;
		vars->map->dimensions.z *= ZOOM_IN_EFFECT;
	}
	else if (keycode == MIN)
	{
		vars->map->dimensions.x *= ZOOM_OUT_EFFECT;
		vars->map->dimensions.y *= ZOOM_OUT_EFFECT;
		vars->map->dimensions.z *= ZOOM_OUT_EFFECT;
	}
	else
		return (more_keys_to_handle(keycode, vars));
	return (0);
}
