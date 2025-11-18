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
	player->movespeed = 6;
	player->c = cub3d->map[i][j];
	cub3d->map[i][j] = '0';
	cub3d->player.position[0] = cub3d->player.position[0] * SQUARE_SIZE
		- SQUARE_SIZE / 2;
	cub3d->player.position[1] = cub3d->player.position[1] * SQUARE_SIZE
		- SQUARE_SIZE / 2;
	cub3d->player.rotation_speed = 0.1;
	cub3d->player.angle = atan2(-player->dir[1], player->dir[0]);
}

void	config_player(t_cub3d *cub3d, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cub3d->map[i])
	{
		while (cub3d->map[i][j])
		{
			if (cub3d->map[i][j] == 'N' || cub3d->map[i][j] == 'S'
				|| cub3d->map[i][j] == 'E' || cub3d->map[i][j] == 'W')
			{
				player->position[0] = j + 1;
				player->position[1] = i + 1;
				break ;
			}
			j++;
		}
		if (cub3d->map[i][j] && (cub3d->map[i][j] == 'N'
				|| cub3d->map[i][j] == 'S' || cub3d->map[i][j] == 'E'
				|| cub3d->map[i][j] == 'W'))
			break ;
		j = 0;
		i++;
	}
	init_status(cub3d, player, i, j);
}
