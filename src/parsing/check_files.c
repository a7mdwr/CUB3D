/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/11/18 16:17:41 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/18 16:17:41 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	open_xpm_helper(t_cub3d *cub3d)
{
	cub3d->fd_no = open(cub3d->no, O_RDONLY);
	if (!cub3d->no || cub3d->fd_no < 0)
	{
		close(cub3d->fd_no);
		ft_error("Failed to open NO texture", 66, cub3d);
	}
	else
		close(cub3d->fd_no);
	cub3d->fd_so = open(cub3d->so, O_RDONLY);
	if (!cub3d->so || cub3d->fd_so < 0)
	{
		close(cub3d->fd_so);
		ft_error("Failed to open SO texture", 66, cub3d);
	}
	else
		close(cub3d->fd_so);
}

void	open_xpm(t_cub3d *cub3d)
{
	open_xpm_helper(cub3d);
	cub3d->fd_we = open(cub3d->we, O_RDONLY);
	if (!cub3d->we || cub3d->fd_we < 0)
	{
		close(cub3d->fd_we);
		ft_error("Failed to open WE texture", 66, cub3d);
	}
	else
		close(cub3d->fd_we);
	cub3d->fd_ea = open(cub3d->ea, O_RDONLY);
	if (!cub3d->ea || cub3d->fd_ea < 0)
	{
		close(cub3d->fd_ea);
		ft_error("Failed to open EA texture", 66, cub3d);
	}
	else
		close(cub3d->fd_ea);
}

void	check_name(t_cub3d *cub3d)
{
	int		len;
	char	*filename;

	filename = NULL;
	filename = cub3d->filename;
	if (!filename)
		ft_error("No filename provided", 65, cub3d);
	len = ft_strlen(filename);
	if (len <= 4)
		ft_error("Invalid file name. must be more than 4 chars", 65, cub3d);
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		ft_error("Invalid file name. Must end with .cub", 65, cub3d);
}

int	ends_with_xpm(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 4)
		return (0);
	return (ft_strcmp(str + len - 4, ".xpm") == 0);
}

void	check_names(t_cub3d *cub3d)
{
	if (!ends_with_xpm(cub3d->no) || !ends_with_xpm(cub3d->so)
		|| !ends_with_xpm(cub3d->we) || !ends_with_xpm(cub3d->ea))
	{
		ft_error("Texture path must end with .xpm", 65, cub3d);
	}
}
