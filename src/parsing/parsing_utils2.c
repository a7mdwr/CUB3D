/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:31:27 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/24 15:33:03 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_identifier(char *line, char *id)
{
	int	i;

	i = 0;
	while (id[i] && line[i] == id[i])
		i++;
	if (id[i] == '\0' && (line[i] == ' ' || line[i] == '\t'))
		return (1);
	return (0);
}

int	check_max_size(t_cub3d *cub)
{
	int	i;
	int	len;
	int	max_len;

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
	char		*new_row;

	i = 0;
	max_len = check_max_size(cub);
	while (cub->map[i])
	{
		if (ft_strlen(cub->map[i]) < max_len)
		{
			new_row = safe_malloc(sizeof(char) * (max_len + 1));
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
