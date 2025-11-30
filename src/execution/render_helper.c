/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:45:47 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/30 14:16:53 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cast_ray_helper(t_cast_elements *cast_elements)
{
	if (cast_elements->ray_dir_x < 0)
	{
		cast_elements->step_x = -1;
		cast_elements->side_dist_x = (cast_elements->ray_x
				- cast_elements->map_x) * cast_elements->delta_dist_x;
	}
	else
	{
		cast_elements->step_x = 1;
		cast_elements->side_dist_x = (cast_elements->map_x + 1.0
				- cast_elements->ray_x) * cast_elements->delta_dist_x;
	}
	if (cast_elements->ray_dir_y < 0)
	{
		cast_elements->step_y = -1;
		cast_elements->side_dist_y = (cast_elements->ray_y
				- cast_elements->map_y) * cast_elements->delta_dist_y;
	}
	else
	{
		cast_elements->step_y = 1;
		cast_elements->side_dist_y = (cast_elements->map_y + 1.0
				- cast_elements->ray_y) * cast_elements->delta_dist_y;
	}
	cast_elements->hit = 0;
}

void	init_compunents(t_cub3d *cub3d, t_cast_elements *cast_elements,
		double ray_angle)
{
	cast_elements->ray_x = cub3d->player.position[0] / SQUARE_SIZE;
	cast_elements->ray_y = cub3d->player.position[1] / SQUARE_SIZE;
	cast_elements->ray_dir_x = cos(ray_angle);
	cast_elements->ray_dir_y = -sin(ray_angle);
	cast_elements->map_x = (int)cast_elements->ray_x;
	cast_elements->map_y = (int)cast_elements->ray_y;
	cast_elements->delta_dist_x = fabs(1 / cast_elements->ray_dir_x);
	cast_elements->delta_dist_y = fabs(1 / cast_elements->ray_dir_y);
}

void	decide_hit(t_cast_elements *cast_elements)
{
	if (cast_elements->side_dist_x < cast_elements->side_dist_y)
	{
		cast_elements->side_dist_x += cast_elements->delta_dist_x;
		cast_elements->map_x += cast_elements->step_x;
		cast_elements->side = 0;
	}
	else
	{
		cast_elements->side_dist_y += cast_elements->delta_dist_y;
		cast_elements->map_y += cast_elements->step_y;
		cast_elements->side = 1;
	}
}

double	cast_ray(t_cub3d *cub3d, double ray_angle)
{
	t_cast_elements	cast_elements;

	init_compunents(cub3d, &cast_elements, ray_angle);
	cast_ray_helper(&cast_elements);
	while (cast_elements.hit == 0)
	{
		decide_hit(&cast_elements);
		if (cub3d->map[cast_elements.map_y][cast_elements.map_x] == '1')
			cast_elements.hit = 1;
	}
	if (cast_elements.side == 0)
		cast_elements.perp_wall_dist = (cast_elements.map_x
				- cast_elements.ray_x + (1 - cast_elements.step_x) / 2)
			/ cast_elements.ray_dir_x;
	else
		cast_elements.perp_wall_dist = (cast_elements.map_y
				- cast_elements.ray_y + (1 - cast_elements.step_y) / 2)
			/ cast_elements.ray_dir_y;
	return (cast_elements.perp_wall_dist * SQUARE_SIZE);
}

double	cast_ray_side(t_cub3d *cub3d, double ray_angle)
{
	t_cast_elements	cast_elements;

	init_compunents(cub3d, &cast_elements, ray_angle);
	cast_ray_helper(&cast_elements);
	while (cast_elements.hit == 0)
	{
		decide_hit(&cast_elements);
		if (cub3d->map[cast_elements.map_y][cast_elements.map_x] == '1')
			cast_elements.hit = 1;
	}
	return (cast_elements.side);
}
