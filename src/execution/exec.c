/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:05:08 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/18 17:05:41 by zsid-ele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_release(int keycode, t_cub3d *cub3d)
{
	(void)cub3d;
	(void)keycode;
	return (0);
}

int	execution_exit(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[0].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[1].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[2].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[3].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->img.img);
	mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	ahasna(cub3d);
	printf("exit in clean way after freeing\n");
	exit(0);
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
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, keys_pressed, cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, game_loop, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, execution_exit, cub3d);
	mlx_loop(cub3d->mlx.mlx);
}
