/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reneder_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zsid-ele <zsid-ele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:16:31 by zsid-ele          #+#    #+#             */
/*   Updated: 2025/11/18 17:16:31 by zsid-ele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct s_cast_elements
{
    double ray_x;
    double ray_y;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    int step_x;
    int step_y;
    double side_dist_x;
    double side_dist_y;
    int hit;
    int side;
    double perp_wall_dist;
}               t_cast_elements;


void    cast_ray_helper(t_cast_elements *cast_elements)
{
    cast_elements->delta_dist_x = fabs(1 / cast_elements->ray_dir_x);// the exact steps to stay on to stay on the same ditr
    cast_elements->delta_dist_y = fabs(1 / cast_elements->ray_dir_y);
    if (cast_elements->ray_dir_x < 0)// by this we caqn understand which side it will hit the4 left or rigt 
    {
        cast_elements->step_x = -1;
        cast_elements->side_dist_x = (cast_elements->ray_x - cast_elements->map_x) * cast_elements->delta_dist_x;
    }
    else
    {
        cast_elements->step_x = 1;
        cast_elements->side_dist_x = (cast_elements->map_x + 1.0 - cast_elements->ray_x) * cast_elements->delta_dist_x;// becouse map_x will always be smaller becouse it alwasys the int part and we need the float part to decided the length of the step
    }
    if (cast_elements->ray_dir_y < 0)
    {
        cast_elements->step_y = -1;
        cast_elements->side_dist_y = (cast_elements->ray_y - cast_elements->map_y) * cast_elements->delta_dist_y;
    }
    else
    {
        cast_elements->step_y = 1;
        cast_elements->side_dist_y = (cast_elements->map_y + 1.0 - cast_elements->ray_y) * cast_elements->delta_dist_y;
    }
    cast_elements->hit = 0;
}

double  cast_ray(t_cub3d    *cub3d, double  ray_angle)
{
    t_cast_elements cast_elements;

    cast_elements.ray_x = cub3d->player.position[0] / SQUARE_SIZE;;
    cast_elements.ray_y = cub3d->player.position[1] / SQUARE_SIZE;
    cast_elements.ray_dir_x = cos(ray_angle);
    cast_elements.ray_dir_y = -sin(ray_angle);
    cast_elements.map_x = (int)cast_elements.ray_x;
    cast_elements.map_y = (int)cast_elements.ray_y;
    cast_ray_helper(&cast_elements);
    while (cast_elements.hit == 0)
    {
        if (cast_elements.side_dist_x < cast_elements.side_dist_y)
        {
            cast_elements.side_dist_x += cast_elements.delta_dist_x;
            cast_elements.map_x += cast_elements.step_x;
            cast_elements.side = 0;
        }
        else
        {
            cast_elements.side_dist_y += cast_elements.delta_dist_y;
            cast_elements.map_y += cast_elements.step_y;
            cast_elements.side = 1;
        }

        if (cub3d->map[cast_elements.map_y][cast_elements.map_x] == '1')
        cast_elements.hit = 1;
    }
    if (cast_elements.side == 0)////////////////////////-------- from the ray equation ray_position = ray_origin + ray_direction * distance 
    cast_elements.perp_wall_dist = (cast_elements.map_x - cast_elements.ray_x + (1 - cast_elements.step_x) / 2) / cast_elements.ray_dir_x;
    else
    cast_elements.perp_wall_dist = (cast_elements.map_y - cast_elements.ray_y + (1 - cast_elements.step_y) / 2) / cast_elements.ray_dir_y;
    return (cast_elements.perp_wall_dist * SQUARE_SIZE);
}

double  cast_ray_side(t_cub3d    *cub3d, double  ray_angle)
{
    t_cast_elements cast_elements;

    cast_elements.ray_x = cub3d->player.position[0] / SQUARE_SIZE;;
    cast_elements.ray_y = cub3d->player.position[1] / SQUARE_SIZE;
    cast_elements.ray_dir_x = cos(ray_angle);
    cast_elements.ray_dir_y = -sin(ray_angle);
    cast_elements.map_x = (int)cast_elements.ray_x;
    cast_elements.map_y = (int)cast_elements.ray_y;
    cast_elements.delta_dist_x = fabs(1 / cast_elements.ray_dir_x);
    cast_elements.delta_dist_y = fabs(1 / cast_elements.ray_dir_y);
    cast_ray_helper(&cast_elements);
    while (cast_elements.hit == 0)
    {
        if (cast_elements.side_dist_x < cast_elements.side_dist_y)
        {
            cast_elements.side_dist_x += cast_elements.delta_dist_x;
            cast_elements.map_x += cast_elements.step_x;
            cast_elements.side = 0;
        }
        else
        {
            cast_elements.side_dist_y += cast_elements.delta_dist_y;
            cast_elements.map_y += cast_elements.step_y;
            cast_elements.side = 1;
        }

        if (cub3d->map[cast_elements.map_y][cast_elements.map_x] == '1')
            cast_elements.hit = 1;
    }
    return (cast_elements.side);
}

typedef struct s_rendered_elements
{
    double camera_x;
    double wall_x;
    int line_height;
    int draw_start;
    int draw_end;
    double wall_dist;
    double corrected_dist;
    double ray_angle;
    double ray_dir_x;
    double ray_dir_y;
    double ray_x;
    double ray_y;
    int tex_y;
    int tex_x;
    int side;
    int tex_id;
    int color;
    int x;
    int y;
    int d;
}               t_rendered_elements;







void    render_image(t_cub3d *cub3d, t_rendered_elements *re)
{
    while (re->y < re->draw_start)
    {
        re->color = rbga_color(cub3d->ceiling[0],cub3d->ceiling[1], cub3d->ceiling[2], 0 );
        img_pixel_put(&cub3d->img, re->x, re->y, re->color);
        re->y++;
    }
    while (re->y < re->draw_end)
    {
        re->d = (re->y - re->draw_start);
        re->tex_y = ((re->d* cub3d->textures[re->tex_id].height) / re->line_height) ;

        re->color = get_tex_pixel(&cub3d->textures[re->tex_id], re->tex_x, re->tex_y);
        img_pixel_put(&cub3d->img, re->x, re->y, re->color);
        re->y++;
    }
    re->y = re->draw_end;
    while (re->y < cub3d->mlx.size_y -1)
    {
        re->color = rbga_color(cub3d->floor[0],cub3d->floor[1], cub3d->floor[2], 0 );
        img_pixel_put(&cub3d->img, re->x, re->y, re->color);
        re->y++;
    }
}

void    decide_scene(t_cub3d *cub3d, t_rendered_elements *re)
{
    if (re->draw_start < 0)
    re->draw_start = 0;
if (re->draw_end >= cub3d->mlx.size_y) 
re->draw_end = cub3d->mlx.size_y - 1;
re->side = cast_ray_side(cub3d, re->ray_angle); // 0=vert,1=hor
re->ray_x = cub3d->player.position[0] / SQUARE_SIZE;
re->ray_y = cub3d->player.position[1] / SQUARE_SIZE;
if (re->side == 0)
re->wall_x = re->ray_y +re->corrected_dist * re->ray_dir_y;
else
re->wall_x = re->ray_x + re->corrected_dist * re->ray_dir_x;
re->wall_x -= floor(re->wall_x);
if (re->side == 0 && re->ray_dir_x > 0) 
{ 
    re->tex_id = 3; 
    re->wall_x = 1 - re->wall_x; 
} // East
else if (re->side == 0 && re->ray_dir_x < 0) 
re->tex_id = 2; // West
else if (re->side == 1 && re->ray_dir_y > 0) 
re->tex_id = 1; // South
else 
{ 
    re->tex_id = 0; 
    re->wall_x = 1 - re->wall_x; 
}
re->tex_x = (int)(re->wall_x * cub3d->textures[re->tex_id].width);
re->y = 0;
}

void render_scene(t_cub3d *cub3d)
{
    t_rendered_elements re;
    ft_memset(cub3d->img.addr, 0, cub3d->img.line_length * cub3d->img.height);

    re.x = 0;
    while (re.x < cub3d->mlx.size_x)
    {
        re.camera_x = (2 * re.x / (double)cub3d->mlx.size_x) - 1;// CONVERT THE CAMERA COORDONATE TO 1 _> -1
        re.ray_angle = cub3d->player.angle + (re.camera_x * (FOV / 2));// this is used for colum by column it move the vison slighthly everytime 
        re.ray_dir_x = cos(re.ray_angle);
        re.ray_dir_y = -sin(re.ray_angle);
        re.wall_dist = cast_ray(cub3d, re.ray_angle);
        re.corrected_dist = re.wall_dist * cos(re.ray_angle - cub3d->player.angle);
        re.line_height = (int)(SQUARE_SIZE *cub3d->mlx.size_y / re.corrected_dist);
        re.draw_start = -re.line_height / 2 + cub3d->mlx.size_y / 2;
        re.draw_end   = re.line_height / 2 + cub3d->mlx.size_y / 2;
        decide_scene(cub3d, &re);
        render_image(cub3d, &re);
        re.x++;    
    }
    mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win, cub3d->img.img, 0, 0);
}
