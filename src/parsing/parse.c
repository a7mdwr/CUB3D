/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:33:02 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/16 19:53:59 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int check_max_size(t_cub3d *cub)
{
    int i;
    int len;
    int max_len;

    i = 0;
    max_len = 0;
    while (cub->map[i])
	{
		len = ft_strlen(cub->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
    return (max_len);
}

void	normalize_map(t_cub3d *cub)
{
	size_t		i;
	size_t		j;
	size_t		max_len;
	char	*new_row;

	i = 0;
	max_len = check_max_size(cub);
	while (cub->map[i])
	{
		if (ft_strlen(cub->map[i]) < max_len)
		{
			new_row = malloc(sizeof(char) * (max_len + 1));
			if (!new_row)
				return ;
			ft_strcpy(new_row, cub->map[i]);
			j = ft_strlen(cub->map[i]);
			while (j < max_len)
			{
				new_row[j] = ' ';
				j++;
			}
			new_row[max_len] = '\0';
			free(cub->map[i]);
			cub->map[i] = new_row;
		}
		i++;
	}
}

void    main_parce(t_cub3d  *cub3d)
{
    check_name(cub3d);
    cub3d->fd_cub = open(cub3d->filename, O_RDONLY);
    if (0 > cub3d->fd_cub)
        error("Cannot open input (file not found / permission denied)", 66, cub3d);
    fill_information(cub3d);
	remove_spaces(cub3d);
	check_map(cub3d);
	open_xpm(cub3d);
	check_names(cub3d);
	parce_colors(cub3d);
	print_information(cub3d);
}