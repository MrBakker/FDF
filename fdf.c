/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/14 13:37:32 by jbakker       #+#    #+#                 */
/*   Updated: 2024/05/22 14:14:57 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	exit_program(t_vars *vars)
{
	if (vars->map)
	{
		if (vars->map->colors)
			free(vars->map->colors);
		if (vars->map->lines)
			free(vars->map->lines);
		if (vars->map->map)
			free(vars->map->map);
		free(vars->map);
	}
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	if (errno == 0)
		perror("Error");
	else
		ft_printf("%sProgram terminated%s\n", RED, DEFAULT);
	exit(0);
	return (0);
}

static void	setup_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, ">>> FDF <<<");
	vars->screen_width = 1920;
	vars->screen_height = 1080;
	mlx_hook(vars->win, KEY_PRESS, 1L << 0, handle_keypress, vars);
	mlx_hook(vars->win, MOUSE_MOVE, 1L << 6, handle_mouse_drag, vars);
	mlx_hook(vars->win, MOUSE_DOWN, 1L << 2, mouse_down, vars);
	mlx_hook(vars->win, MOUSE_UP, 1L << 3, mouse_up, vars);
	mlx_hook(vars->win, EXIT, 1L << 17, exit_program, vars);
	mlx_loop_hook(vars->mlx, render_frame, vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars = (t_vars){0, 0, 0, 0, 0, 0, 0, 0, 0};
	if (argc != 2)
		return (ft_printf("Usage: %s <filename>\n", argv[0]), 0);
	if (!ft_endswith(argv[1], ".fdf"))
		return (ft_printf("%sFile must be of type .fdf%s\n", RED, DEFAULT), 1);
	vars.map = fetch_map(argv[1]);
	if (!vars.map)
		return (ft_printf("%sError: could not fetch map%s\n", RED, DEFAULT), 1);
	setup_window(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
