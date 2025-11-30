/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configur_mlx.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 12:39:18 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/29 12:39:18 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	config_mlx(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	(void)cub3d;
	while (cub3d->map[y])
		y++;
	cub3d->mlx.size_y = 1024;
	x = ft_strlen(cub3d->map[0]);
	cub3d->mlx.size_x = 1024;
}

void	load_texture(t_cub3d *cub3d, int id, char *path)
{
	cub3d->textures[id].img = mlx_xpm_file_to_image(cub3d->mlx.mlx, path,
			&cub3d->textures[id].width, &cub3d->textures[id].height);
	if (!cub3d->textures[id].img)
	{
		printf("Error\nfailed to load texture %s\n", path);
		exit(1);
	}
	cub3d->textures[id].addr = mlx_get_data_addr(cub3d->textures[id].img,
			&cub3d->textures[id].bpp, &cub3d->textures[id].line_length,
			&cub3d->textures[id].endian);
}

int	get_tex_pixel(t_texture *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
