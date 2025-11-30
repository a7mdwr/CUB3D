/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reneder_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/18 17:16:31 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/18 17:16:31 by zsid-ele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	render_walls(t_cub3d *cub3d, t_rendered_elements *re)
{
	int	y;
	int	color;
	int	tex_y;

	re->step = (double)cub3d->textures[re->tex_id].height
		/ (double)re->line_height;
	re->tex_pos = (re->draw_start - cub3d->mlx.size_y / 2 + re->line_height / 2)
		* re->step;
	y = re->draw_start;
	while (y < re->draw_end)
	{
		tex_y = (int)re->tex_pos;
		re->tex_pos += re->step;
		color = get_tex_pixel(&cub3d->textures[re->tex_id], re->tex_x, tex_y);
		img_pixel_put(&cub3d->img, re->x, y, color);
		y++;
	}
}

void	render_image(t_cub3d *cub3d, t_rendered_elements *re)
{
	while (re->y < re->draw_start)
	{
		re->color = rgb_color(cub3d->ceiling[0], cub3d->ceiling[1],
				cub3d->ceiling[2], 0);
		img_pixel_put(&cub3d->img, re->x, re->y, re->color);
		re->y++;
	}
	render_walls(cub3d, re);
	re->y = re->draw_end;
	while (re->y < cub3d->mlx.size_y - 1)
	{
		re->color = rgb_color(cub3d->floor[0], cub3d->floor[1], cub3d->floor[2],
				0);
		img_pixel_put(&cub3d->img, re->x, re->y, re->color);
		re->y++;
	}
}

void	decide_wall(t_rendered_elements *re)
{
	if (re->side == 0 && re->ray_dir_x > 0)
	{
		re->tex_id = 3;
		re->wall_x = 1 - re->wall_x;
	}
	else if (re->side == 0 && re->ray_dir_x < 0)
		re->tex_id = 2;
	else if (re->side == 1 && re->ray_dir_y > 0)
		re->tex_id = 1;
	else
	{
		re->tex_id = 0;
		re->wall_x = 1 - re->wall_x;
	}
}

void	decide_scene(t_cub3d *cub3d, t_rendered_elements *re)
{
	if (re->draw_start < 0)
		re->draw_start = 0;
	if (re->draw_end >= cub3d->mlx.size_y)
		re->draw_end = cub3d->mlx.size_y - 1;
	re->side = cast_ray_side(cub3d, re->ray_angle);
	re->ray_x = cub3d->player.position[0] / SQUARE_SIZE;
	re->ray_y = cub3d->player.position[1] / SQUARE_SIZE;
	if (re->side == 0)
		re->wall_x = re->ray_y + re->corrected_dist * re->ray_dir_y;
	else
		re->wall_x = re->ray_x + re->corrected_dist * re->ray_dir_x;
	re->wall_x -= floor(re->wall_x);
	decide_wall(re);
	re->tex_x = (int)(re->wall_x * cub3d->textures[re->tex_id].width);
	re->y = 0;
}

void	render_scene(t_cub3d *cub3d)
{
	t_rendered_elements	re;

	re.x = 0;
	ft_memset(cub3d->img.addr, 0, cub3d->img.line_length * cub3d->img.height);
	while (re.x < cub3d->mlx.size_x)
	{
		re.camera_x = (2 * re.x / (double)cub3d->mlx.size_x) - 1;
		re.ray_angle = cub3d->player.angle + (re.camera_x * (FOV / 2));
		re.ray_dir_x = cos(re.ray_angle);
		re.ray_dir_y = -sin(re.ray_angle);
		re.wall_dist = cast_ray(cub3d, re.ray_angle);
		re.corrected_dist = re.wall_dist * cos(re.ray_angle
				- cub3d->player.angle);
		re.line_height = (int)(SQUARE_SIZE * cub3d->mlx.size_y
				/ re.corrected_dist);
		re.draw_start = -re.line_height / 2 + cub3d->mlx.size_y / 2;
		re.draw_end = re.line_height / 2 + cub3d->mlx.size_y / 2;
		decide_scene(cub3d, &re);
		render_image(cub3d, &re);
		re.x++;
	}
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->img.img, 0,
		0);
}
