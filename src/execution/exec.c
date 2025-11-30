/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:08 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/30 14:16:02 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	game_loop(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;
	render_scene(cub3d);
	return (0);
}

int	key_press(int keycode, t_cub3d *cub)
{
	if (keycode == 13)
		cub->keys.w = 1;
	if (keycode == 1)
		cub->keys.s = 1;
	if (keycode == 0)
		cub->keys.a = 1;
	if (keycode == 2)
		cub->keys.d = 1;
	if (keycode == 123)
		cub->keys.left = 1;
	if (keycode == 124)
		cub->keys.right = 1;
	if (keycode == 53)
		execution_exit(cub);
	return (0);
}

static int	key_release(int keycode, t_cub3d *cub)
{
	if (keycode == 13)
		cub->keys.w = 0;
	if (keycode == 1)
		cub->keys.s = 0;
	if (keycode == 0)
		cub->keys.a = 0;
	if (keycode == 2)
		cub->keys.d = 0;
	if (keycode == 123)
		cub->keys.left = 0;
	if (keycode == 124)
		cub->keys.right = 0;
	return (0);
}

static int	update(t_cub3d *cub)
{
	int	tx;
	int	ty;

	ty = 0;
	tx = 0;
	if (cub->keys.left)
		cub->player.angle -= cub->player.rotation_speed;
	if (cub->keys.right)
		cub->player.angle += cub->player.rotation_speed;
	cub->player.dir[0] = cos(cub->player.angle);
	cub->player.dir[1] = -sin(cub->player.angle);
	if (cub->keys.a)
		move_vertical(cub, &tx, &ty, 0);
	if (cub->keys.d)
		move_vertical(cub, &tx, &ty, 2);
	if (cub->keys.w)
		move_horizontal(cub, &tx, &ty, 13);
	if (cub->keys.s)
		move_horizontal(cub, &tx, &ty, 1);
	render_scene(cub);
	return (0);
}

void	main_execution(t_cub3d *cub3d)
{
	config_mlx(cub3d);
	cub3d->mlx.mlx = mlx_init();
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.mlx, cub3d->mlx.size_x,
			cub3d->mlx.size_y, "CUB3D");
	cub3d->img.img = mlx_new_image(cub3d->mlx.mlx, cub3d->mlx.size_x,
			cub3d->mlx.size_y);
	cub3d->img.addr = mlx_get_data_addr(cub3d->img.img, &cub3d->img.bpp,
			&cub3d->img.line_length, &cub3d->img.endian);
	cub3d->img.width = cub3d->mlx.size_x;
	cub3d->img.height = cub3d->mlx.size_y;
	load_texture(cub3d, 0, cub3d->no);
	load_texture(cub3d, 1, cub3d->so);
	load_texture(cub3d, 2, cub3d->ea);
	load_texture(cub3d, 3, cub3d->we);
	config_player(cub3d, &cub3d->player);
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, key_release, cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, update, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, execution_exit, cub3d);
	mlx_loop(cub3d->mlx.mlx);
}
