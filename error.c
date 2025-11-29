/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:58:01 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/29 11:05:25 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	*safe_malloc(size_t size)
{
	void	*a;
	t_cub3d	cub3d;

	a = malloc(size);
	if (a == NULL)
	{
		ft_error("Error: malloc failed\n", 71, &cub3d);
		return (0);
	}
	return (a);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
	else
		return ;
}

void	ahasna(t_cub3d *cub3d)
{
	free(cub3d->c);
	free(cub3d->f);
	free(cub3d->no);
	free(cub3d->so);
	free(cub3d->we);
	free(cub3d->ea);
	if (cub3d->map)
		free_array(cub3d->map);
}

int	execution_exit(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[0].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[1].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[2].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->textures[3].img);
	mlx_destroy_image(cub3d->mlx.mlx, cub3d->img.img);
	mlx_clear_window(cub3d->mlx.mlx, cub3d->mlx.win);
	mlx_destroy_window(cub3d->mlx.mlx, cub3d->mlx.win);
	ahasna(cub3d);
	printf("exit in clean way after freeing\n");
	exit(0);
}

void	ft_error(char *error, int exitcode, t_cub3d *cub3d)
{
	ahasna(cub3d);
	printf("\033[31mError\nExit code(%d)->%s\033[0m\n", exitcode, error);
	exit(exitcode);
}
