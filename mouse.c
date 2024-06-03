/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/17 17:41:39 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/17 17:54:02 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	mouse_down(int button, int x, int y, t_vars *vars)
{
	if (button == SCROLL_UP)
	{
		vars->map->dimensions.x *= ZOOM_IN_EFFECT;
		vars->map->dimensions.y *= ZOOM_IN_EFFECT;
		vars->map->dimensions.z *= ZOOM_IN_EFFECT;
	}
	if (button == SCROLL_DOWN)
	{
		vars->map->dimensions.x *= ZOOM_OUT_EFFECT;
		vars->map->dimensions.y *= ZOOM_OUT_EFFECT;
		vars->map->dimensions.z *= ZOOM_OUT_EFFECT;
	}
	if (button == LEFT_CLICK)
		vars->left_mouse_pressed = 1;
	if (button == RIGHT_CLICK)
		vars->right_mouse_pressed = 1;
	vars->mouse_x = x;
	vars->mouse_y = y;
	return (0);
}

int	mouse_up(int button, int x, int y, t_vars *vars)
{
	if (button == LEFT_CLICK)
		vars->left_mouse_pressed = 0;
	if (button == RIGHT_CLICK)
		vars->right_mouse_pressed = 0;
	vars->mouse_x = x;
	vars->mouse_y = y;
	return (0);
}

int	handle_mouse_drag(int x, int y, t_vars *vars)
{
	if (vars->left_mouse_pressed == 1)
	{
		vars->map->offset_x += (x - vars->mouse_x);
		vars->map->offset_y += (y - vars->mouse_y);
	}
	if (vars->right_mouse_pressed == 1)
	{
		vars->map->x_rotation += (y - vars->mouse_y) * ROTATION_EFFECT * 0.1;
		vars->map->y_rotation += (x - vars->mouse_x) * ROTATION_EFFECT * 0.1;
	}
	vars->mouse_x = x;
	vars->mouse_y = y;
	return (0);
}
