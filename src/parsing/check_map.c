/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:18:06 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/18 16:18:06 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(char **map, int x, int y, int *valid)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x])
	{
		*valid = 0;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, valid);
	flood_fill(map, x - 1, y, valid);
	flood_fill(map, x, y + 1, valid);
	flood_fill(map, x, y - 1, valid);
}

void	check_closed_map(char **map, int player_x, int player_y, t_cub3d *cub3d)
{
	char	**copy;
	int		valid;
	int		j;
	int		i;

	i = 0;
	j = 0;
	valid = 1;
	while (map[i])
		i++;
	copy = safe_malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		copy[j] = ft_strdup(map[j]);
		j++;
	}
	copy[i] = NULL;
	flood_fill(copy, player_x, player_y, &valid);
	free_array(copy);
	if (!valid)
		ft_error("Map is not closed", 65, cub3d);
}

void	find_player(char **map, int *px, int *py, t_cub3d *cub3d)
{
	t_variables	v;

	v.y = 0;
	v.x = 0;
	v.found = 0;
	while (map[v.y])
	{
		v.x = 0;
		while (map[v.y][v.x])
		{
			if (map[v.y][v.x] == 'N' || map[v.y][v.x] == 'S' ||
				map[v.y][v.x] == 'E' || map[v.y][v.x] == 'W')
			{
				if (v.found)
					ft_error("Multiple player positions", 65, cub3d);
				*px = v.x;
				*py = v.y;
				v.found = 1;
			}
			v.x++;
		}
		v.y++;
	}
	if (!v.found)
		ft_error("No player found in map", 65, cub3d);
}

void	check_undfind_simple(char	**map, t_cub3d	*cub3d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j] != '\0')
		{
			if (map[i][j] != 'N' && map[i][j] != 'E' && map[i][j] != 'W' &&
			map[i][j] != 'S' && map[i][j] != ' ' && map[i][j] != '1' &&
				map[i][j] != '0' && map[i][j] != '\n')
				ft_error("Data format error (bad input file)", 65, cub3d);
			j++;
		}
		j = 0;
		i++;
	}
}

void	check_map(t_cub3d *cub3d)
{
	int	player_x;
	int	player_y;

	if (!cub3d->map)
		ft_error("No map found", 65, cub3d);
	normalize_map(cub3d);
	find_player(cub3d->map, &player_x, &player_y, cub3d);
	check_closed_map(cub3d->map, player_x, player_y, cub3d);
}
