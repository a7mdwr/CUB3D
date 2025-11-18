#include "../include/cub3d.h"
int i = 0;
int	game_loop(void *param)
{
	t_cub3d	*cub3d;

	cub3d = (t_cub3d *)param;

	render_scene(cub3d);
	return (0);
}

/*
	check_area:
	return 1 if the circle around (test_x, test_y)
	touches a wall ('1'), else 0.
*/
int	check_area(int test_x, int test_y, t_cub3d *cub3d)
{
	int	cx;
	int	cy;
	int	x;

	cx = test_x;
	cy = test_y;
	x = cx - RADIUS;
	while (x <= cx + RADIUS)
	{
		int	y = cy - RADIUS;
		while (y <= cy + RADIUS)
		{
			int	dx = x - cx;
			int	dy = y - cy;
			int	curr_x;
			int	curr_y;

			if (squr(dx) + squr(dy) <= squr(RADIUS))
			{
				curr_x = x / SQUARE_SIZE;
				curr_y = y / SQUARE_SIZE;
				if (curr_x < 0 || curr_y < 0
					|| !cub3d->map[curr_y]
					|| !cub3d->map[curr_y][curr_x]
					|| cub3d->map[curr_y][curr_x] == '1')
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

int	keys_pressed(int keycode, void *param)
{
	t_cub3d	*cub3d;
	int		test_x;
	int		test_y;

	cub3d = (t_cub3d *)param;
	// ESC -> exit
	if (keycode == 53)
	{
		mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
		ahasna(cub3d);
		exit(0);
	}
	// RIGHT ARROW -> rotate right
	if (keycode == 124)
		cub3d->player.angle += cub3d->player.rotation_speed;
	// LEFT ARROW -> rotate left
	if (keycode == 123)
		cub3d->player.angle -= cub3d->player.rotation_speed;
	cub3d->player.dir[0] = cos(cub3d->player.angle);
	cub3d->player.dir[1] = -sin(cub3d->player.angle);
		
	// W -> forward
	if (keycode == 13)
	{
		test_x = cub3d->player.position[0] + cub3d->player.movespeed * cub3d->player.dir[0];
		test_y = cub3d->player.position[1] + cub3d->player.movespeed * cub3d->player.dir[1];

		if (check_area(test_x, test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = test_x;
			cub3d->player.position[1] = test_y;
		}
	}
	// S -> backward
	if (keycode == 1)
	{
		test_x = cub3d->player.position[0] - cub3d->player.movespeed * cub3d->player.dir[0];
test_y = cub3d->player.position[1] - cub3d->player.movespeed * cub3d->player.dir[1];

		if (check_area(test_x, test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = test_x;
			cub3d->player.position[1] = test_y;
		}
	}
	// A -> strafe left
	if (keycode == 0)
	{
		test_x = cub3d->player.position[0] - cub3d->player.movespeed * cub3d->player.dir[1];
test_y = cub3d->player.position[1] + cub3d->player.movespeed * cub3d->player.dir[0];

		if (check_area(test_x, test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = test_x;
			cub3d->player.position[1] = test_y;
		}
	}
	// D -> strafe right
	if (keycode == 2)
	{
		test_x = cub3d->player.position[0] + cub3d->player.movespeed * cub3d->player.dir[1];
test_y = cub3d->player.position[1] - cub3d->player.movespeed * cub3d->player.dir[0];

		if (check_area(test_x, test_y, cub3d) == 0)
		{
			cub3d->player.position[0] = test_x;
			cub3d->player.position[1] = test_y;
		}
	}
	// keep angle between 0 and 2π
	if (cub3d->player.angle < 0)
		cub3d->player.angle += 2 * M_PI;
	if (cub3d->player.angle > 2 * M_PI)
		cub3d->player.angle -= 2 * M_PI;
	return (0);
}
