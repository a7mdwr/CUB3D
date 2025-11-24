/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:14:20 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/24 14:45:01 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	parse_color_helper(char **parts, int *dest, t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (parts[i][j])
		{
			if (!ft_isdigit(parts[i][j]))
			{
				free_array(parts);
				ft_error("Color values must a digit!!!", 68, cub3d);
			}
			j++;
		}
		dest[i] = ft_atoi(parts[i]);
		if (dest[i] < 0 || dest[i] > 255)
		{
			free_array(parts);
			ft_error("Color values must be between 0 and 255", 68, cub3d);
		}
		i++;
	}
}

void	parse_color_str(const char *str, int type, t_cub3d *cub3d)
{
	char	**parts;
	int		*dest;

	if (type == 1)
		dest = cub3d->floor;
	else
		dest = cub3d->ceiling;
	parts = ft_split(str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		free_array(parts);
		ft_error("Invalid color format (must be R,G,B)", 67, cub3d);
	}
	parse_color_helper(parts, dest, cub3d);
	free_array(parts);
}

void	parce_colors(t_cub3d *cub3d)
{
	if (cub3d->f)
		parse_color_str(cub3d->f, 1, cub3d);
	if (cub3d->c)
		parse_color_str(cub3d->c, 2, cub3d);
}
