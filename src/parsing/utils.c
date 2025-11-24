/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:21:10 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/18 16:21:10 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	remove_newline(char **cub3d)
{
	int	i;

	i = 0;
	while (cub3d[0][i])
		i++;
	if (cub3d[0][i - 1] == '\n')
		cub3d[0][i - 1] = '\0';
}

int	ft_isspace(unsigned char c)
{
	if (c && c == ' ')
		return (c);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	rgb_color(int r, int g, int b, int a)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
