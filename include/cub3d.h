/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aradwan <aradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:32:44 by aradwan           #+#    #+#             */
/*   Updated: 2025/11/30 14:41:01 by aradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SQUARE_SIZE 24
# define FOV 1.0471975512
# define RES 2
# define RADIUS 1
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

typedef struct s_helper_vars
{
	int			i;
	int			j;
	int			k;

}				t_helper_vars;

typedef struct s_keys
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			left;
	int			right;
}				t_keys;

typedef struct s_rendered_elements
{
	double		camera_x;
	double		wall_x;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_dist;
	double		corrected_dist;
	double		ray_angle;
	double		ray_dir_x;
	double		ray_dir_y;
	double		ray_x;
	double		ray_y;
	int			tex_y;
	int			tex_x;
	int			side;
	int			tex_id;
	int			color;
	int			x;
	int			y;
	int			d;
	double		step;
	double		tex_pos;
}				t_rendered_elements;

typedef struct s_cast_elements
{
	double		ray_x;
	double		ray_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	double		side_dist_x;
	double		side_dist_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
}				t_cast_elements;

typedef struct s_circle_check
{
	int			x;
	int			y;
	int			dx;
	int			dy;
	int			curr_x;
	int			curr_y;
}				t_circle_check;

typedef struct s_variables
{
	int			x;
	int			y;
	int			found;
}				t_variables;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	void		*img;
	char		*addr;
	int			width;
	int			height;
	int			bpp;
	int			line_length;
	int			endian;
}				t_texture;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	int			size_x;
	int			size_y;
}				t_mlx;

typedef struct s_player
{
	double		position[2];
	double		dir[2];
	double		fov[2];
	int			n_rays;
	double		angle;
	int			movespeed;
	float		rotation_speed;
	float		fov_angle;
	char		c;
}				t_player;

typedef struct s_cub3d
{
	t_player	player;
	t_mlx		mlx;
	t_img		img;
	t_texture	textures[4];
	t_keys		keys;
	char		*filename;
	int			fd_cub;
	char		**map;
	char		*no;
	int			fd_no;
	char		*so;
	int			fd_so;
	char		*we;
	int			fd_we;
	char		*ea;
	int			fd_ea;
	char		*c;
	char		*f;
	int			floor[3];
	int			ceiling[3];
	double		new_x;
	double		new_y;
}				t_cub3d;

/* ---------clean exit------------- */
void			ft_error(char *error, int exitcode, t_cub3d *cub3d);
void			ahasna(t_cub3d *cub3d);
void			free_array(char **array);
int				execution_exit(t_cub3d *cub3d);

/* ---------parce------------- */
void			main_parce(t_cub3d *cub3d);
void			check_undfind_simple(char **map, t_cub3d *cub3d);
void			fill_map(t_cub3d *cub3d, char *line);
void			fill_information(t_cub3d *cub3d);
void			check_name(t_cub3d *cub3d);
void			flood_fill(char **map, int x, int y, int *valid);
void			check_closed_map(char **map, int player_x, int player_y,
					t_cub3d *cub3d);
void			find_player(char **map, int *px, int *py, t_cub3d *cub3d);
char			*trim_after_key(const char *line);
char			*trim_until_digit(const char *line);
void			fix_end(t_cub3d *cub3d);
void			remove_spaces(t_cub3d *cub3d);
void			parse_color_str(const char *str, int type, t_cub3d *cub3d);
void			parce_colors(t_cub3d *cub3d);
int				ends_with_xpm(const char *str);
void			check_names(t_cub3d *cub3d);
void			normalize_map(t_cub3d *cub);
void			check_map(t_cub3d *cub3d);
void			open_xpm(t_cub3d *cub3d);
int				is_identifier(char *line, char *id);

/* ---------utils------------- */
int				abs(int i);
int				squr(int num);
int				ft_isspace(unsigned char c);
int				ft_strcmp(const char *s1, const char *s2);
void			remove_newline(char **cub3d);
char			*ft_strcpy(char *dst, const char *src);
void			normalize_map(t_cub3d *cub);
void			*safe_malloc(size_t size);

/* ---------execution------------- */
// mlx config
void			config_mlx(t_cub3d *cub3d);
void			img_pixel_put(t_img *img, int x, int y, int color);
void			load_texture(t_cub3d *cub3d, int id, char *path);
int				get_tex_pixel(t_texture *tex, int x, int y);
// scene
void			main_execution(t_cub3d *cub3d);
void			config_player(t_cub3d *cub3d, t_player *player);
double			cast_ray(t_cub3d *cub3d, double ray_angle);
double			cast_ray_side(t_cub3d *cub3d, double ray_angle);
int				move_horizontal(t_cub3d *cub3d, int *test_x, int *test_y,
					int keycode);
int				move_vertical(t_cub3d *cub3d, int *test_x, int *test_y,
					int keycode);
// main reneder function
void			render_scene(t_cub3d *cub3d);
int				game_loop(void *param);
int				check_area(int test_x, int test_y, t_cub3d *cub3d);
int				keys_pressed(int keycode, void *param);
int				rgb_color(int r, int b, int g, int a);

#endif