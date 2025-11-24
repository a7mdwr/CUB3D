/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:33:02 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/24 15:36:22 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	main_parce(t_cub3d *cub3d)
{
	t_variables	v;

	ft_bzero(&v, sizeof(v));
	check_name(cub3d);
	cub3d->fd_cub = open(cub3d->filename, O_RDONLY);
	if (0 > cub3d->fd_cub)
		ft_error("Cannot open input (file not found)", 66, cub3d);
	fill_information(cub3d);
	remove_spaces(cub3d);
	check_map(cub3d);
	open_xpm(cub3d);
	check_names(cub3d);
	parce_colors(cub3d);
}
