/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configur_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:03:10 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/18 17:03:10 by zsid-ele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_helper(t_cub3d *cub3d, t_player *player, int i, int j)
{
	player->movespeed = 1;
	player->c = cub3d->map[i][j];
	cub3d->map[i][j] = '0';
	cub3d->player.position[0] = cub3d->player.position[0] * SQUARE_SIZE
		- SQUARE_SIZE / 2;
	cub3d->player.position[1] = cub3d->player.position[1] * SQUARE_SIZE
		- SQUARE_SIZE / 2;
	cub3d->player.rotation_speed = 0.070;
	cub3d->player.angle = atan2(-player->dir[1], player->dir[0]);
	return ;
}

void	init_status(t_cub3d *cub3d, t_player *player, int i, int j)
{
	if (cub3d->map[i][j] == 'N')
	{
		player->dir[0] = 0;
		player->dir[1] = -1;
	}
	if (cub3d->map[i][j] == 'W')
	{
		player->dir[0] = -1;
		player->dir[1] = 0;
	}
	if (cub3d->map[i][j] == 'S')
	{
		player->dir[0] = 0;
		player->dir[1] = 1;
	}
	if (cub3d->map[i][j] == 'E')
	{
		player->dir[0] = 1;
		player->dir[1] = 0;
	}
	init_helper(cub3d, player, i, j);
}

void	config_player(t_cub3d *cub3d, t_player *player)
{
	t_helper_vars	v;

	v.i = 0;
	v.j = 0;
	while (cub3d->map[v.i])
	{
		while (cub3d->map[v.i][v.j])
		{
			if (cub3d->map[v.i][v.j] == 'N' || cub3d->map[v.i][v.j] == 'S'
				|| cub3d->map[v.i][v.j] == 'E' || cub3d->map[v.i][v.j] == 'W')
			{
				player->position[0] = v.j + 1;
				player->position[1] = v.i + 1;
				break ;
			}
			v.j++;
		}
		if (cub3d->map[v.i][v.j] && (cub3d->map[v.i][v.j] == 'N'
				|| cub3d->map[v.i][v.j] == 'S' || cub3d->map[v.i][v.j] == 'E'
				|| cub3d->map[v.i][v.j] == 'W'))
			break ;
		v.j = 0;
		v.i++;
	}
	init_status(cub3d, player, v.i, v.j);
}
