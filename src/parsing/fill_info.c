/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:18:39 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/18 16:18:39 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	save_identifier(t_cub3d *cub3d, char *line)
{
	if (is_identifier(line, "NO") && !cub3d->no)
		cub3d->no = ft_strdup(line + 2);
	else if (is_identifier(line, "SO") && !cub3d->so)
		cub3d->so = ft_strdup(line + 2);
	else if (is_identifier(line, "WE") && !cub3d->we)
		cub3d->we = ft_strdup(line + 2);
	else if (is_identifier(line, "EA") && !cub3d->ea)
		cub3d->ea = ft_strdup(line + 2);
	else if (is_identifier(line, "F") && !cub3d->f)
		cub3d->f = ft_strdup(line + 1);
	else if (is_identifier(line, "C") && !cub3d->c)
		cub3d->c = ft_strdup(line + 1);
	else
	{
		free(line);
		ft_error("Duplicate or invalid identifier in .cub file", 67, cub3d);
	}
}

static int	fill_map_helper(t_cub3d *cub3d, char *line)
{
	int		j;
	char	**new;

	j = 0;
	if (line)
	{
		j = 0;
		while (cub3d->map[j])
			j++;
		new = safe_malloc(sizeof(char *) * (j + 2));
		j = 0;
		while (cub3d->map[j])
		{
			new[j] = ft_strdup(cub3d->map[j]);
			j++;
		}
		new[j] = NULL;
		free_array(cub3d->map);
		cub3d->map = new;
		return (1);
	}
	else
		return (0);
}

void	fill_map(t_cub3d *cub3d, char *line)
{
	int	i;

	i = 0;
	cub3d->map = safe_malloc(sizeof(char *) * 2);
	cub3d->map[0] = NULL;
	cub3d->map[1] = NULL;
	while (line)
	{
		if (*line == '\n')
		{
			free(line);
			ft_error("Invalid empty line inside map", 68, cub3d);
		}
		cub3d->map[i] = ft_strdup(line);
		cub3d->map[i + 1] = NULL;
		free(line);
		i++;
		line = get_next_line(cub3d->fd_cub);
		if (!fill_map_helper(cub3d, line))
			break ;
	}
}

static char	*read_identifiers(t_cub3d *cub3d)
{
	char	*line;
	int		found;

	found = 0;
	line = get_next_line(cub3d->fd_cub);
	while (line)
	{
		if (*line != '\n')
		{
			save_identifier(cub3d, line);
			found++;
		}
		free(line);
		line = get_next_line(cub3d->fd_cub);
		if (found == 6 || !line || *line == '1' || *line == '0' || *line == ' ')
			break ;
	}
	if (found < 6)
		ft_error("Missing one or more identifiers \
(NO, SO, WE, EA, F, C)", 68, cub3d);
	return (line);
}

void	fill_information(t_cub3d *cub3d)
{
	char	*line;

	line = read_identifiers(cub3d);
	while (line && *line == '\n')
	{
		free(line);
		line = get_next_line(cub3d->fd_cub);
	}
	if (!line || (*line != '1' && *line != '0' && *line != ' '))
	{
		free(line);
		ft_error("Missing the map or invalid map", 68, cub3d);
	}
	fill_map(cub3d, line);
}
