/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Normlize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/18 16:18:47 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/18 16:18:47 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*trim_after_key(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isspace(line[i]))
		i++;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (ft_strdup(line + i));
}

char	*trim_until_digit(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && !ft_isdigit(line[i]))
		i++;
	return (ft_strdup(line + i));
}

void	fix_end(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (cub3d->no)
		remove_newline(&cub3d->no);
	if (cub3d->so)
		remove_newline(&cub3d->so);
	if (cub3d->we)
		remove_newline(&cub3d->we);
	if (cub3d->ea)
		remove_newline(&cub3d->ea);
	if (cub3d->f)
		remove_newline(&cub3d->f);
	if (cub3d->c)
		remove_newline(&cub3d->c);
	while (cub3d->map[i])
	{
		remove_newline(&cub3d->map[i]);
		i++;
	}
	check_undfind_simple(cub3d->map, cub3d);
}

static void	remove_spaces_helper(t_cub3d *cub3d)
{
	char	*tmp;

	tmp = NULL;
	if (cub3d->ea)
	{
		tmp = trim_after_key(cub3d->ea);
		free(cub3d->ea);
		cub3d->ea = tmp;
	}
	if (cub3d->f)
	{
		tmp = trim_until_digit(cub3d->f);
		free(cub3d->f);
		cub3d->f = tmp;
	}
	if (cub3d->c)
	{
		tmp = trim_until_digit(cub3d->c);
		free(cub3d->c);
		cub3d->c = tmp;
	}
}

void	remove_spaces(t_cub3d *cub3d)
{
	char	*tmp;

	tmp = NULL;
	if (cub3d->no)
	{
		tmp = trim_after_key(cub3d->no);
		free(cub3d->no);
		cub3d->no = tmp;
	}
	if (cub3d->so)
	{
		tmp = trim_after_key(cub3d->so);
		free(cub3d->so);
		cub3d->so = tmp;
	}
	if (cub3d->we)
	{
		tmp = trim_after_key(cub3d->we);
		free(cub3d->we);
		cub3d->we = tmp;
	}
	remove_spaces_helper(cub3d);
	fix_end(cub3d);
}
