/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:32:35 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/29 09:32:35 by zsid-ele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	check_inside_circle(t_cub3d *cub3d, t_circle_check *cc)
{
	if (squr(cc->dx) + squr(cc->dy) <= squr(RADIUS))
	{
		cc->curr_x = cc->x / SQUARE_SIZE;
		cc->curr_y = cc->y / SQUARE_SIZE;
		if (cc->curr_x < 0 || cc->curr_y < 0 || !cub3d->map[cc->curr_y]
			|| !cub3d->map[cc->curr_y][cc->curr_x]
			|| cub3d->map[cc->curr_y][cc->curr_x] == '1')
			return (1);
	}
	return (0);
}

int	check_area(int test_x, int test_y, t_cub3d *cub3d)
{
	t_circle_check	cc;

	cc.x = test_x - RADIUS;
	while (cc.x <= test_x + RADIUS)
	{
		cc.y = test_y - RADIUS;
		while (cc.y <= test_y + RADIUS)
		{
			cc.dx = cc.x - test_x;
			cc.dy = cc.y - test_y;
			check_inside_circle(cub3d, &cc);
			if (check_inside_circle(cub3d, &cc))
				return (1);
			cc.y++;
		}
		cc.x++;
	}
	return (0);
}

int	move_vertical(t_cub3d *cub3d, int *test_x, int *test_y, int keycode)
{
	if (keycode == 0)
	{
		*test_x = cub3d->player.position[0] - cub3d->player.movespeed
			* cub3d->player.dir[1];
		*test_y = cub3d->player.position[1] + cub3d->player.movespeed
			* cub3d->player.dir[0];
		if (check_area(*test_x, *test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = *test_x;
			cub3d->player.position[1] = *test_y;
		}
	}
	if (keycode == 2)
	{
		*test_x = cub3d->player.position[0] + cub3d->player.movespeed
			* cub3d->player.dir[1];
		*test_y = cub3d->player.position[1] - cub3d->player.movespeed
			* cub3d->player.dir[0];
		if (check_area(*test_x, *test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = *test_x;
			cub3d->player.position[1] = *test_y;
		}
	}
	return (0);
}

int	move_horizontal(t_cub3d *cub3d, int *test_x, int *test_y, int keycode)
{
	if (keycode == 13)
	{
		*test_x = cub3d->player.position[0] + cub3d->player.movespeed
			* cub3d->player.dir[0];
		*test_y = cub3d->player.position[1] + cub3d->player.movespeed
			* cub3d->player.dir[1];
		if (check_area(*test_x, *test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = *test_x;
			cub3d->player.position[1] = *test_y;
		}
	}
	if (keycode == 1)
	{
		*test_x = cub3d->player.position[0] - cub3d->player.movespeed
			* cub3d->player.dir[0];
		*test_y = cub3d->player.position[1] - cub3d->player.movespeed
			* cub3d->player.dir[1];
		if (check_area(*test_x, *test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = *test_x;
			cub3d->player.position[1] = *test_y;
		}
	}
	return (0);
}

int	keys_pressed(int keycode, void *param)
{
	t_cub3d	*cub3d;
	int		test_x;
	int		test_y;

	cub3d = (t_cub3d *)param;
	if (keycode == 53)
		execution_exit(cub3d);
	if (keycode == 124)
		cub3d->player.angle += cub3d->player.rotation_speed;
	if (keycode == 123)
		cub3d->player.angle -= cub3d->player.rotation_speed;
	cub3d->player.dir[0] = cos(cub3d->player.angle);
	cub3d->player.dir[1] = -sin(cub3d->player.angle);
	move_vertical(cub3d, &test_x, &test_y, keycode);
	move_horizontal(cub3d, &test_x, &test_y, keycode);
	return (0);
}
