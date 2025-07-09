/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/01 15:09:31 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIN_W 1920
# define WIN_H 1080

# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/minilibx-linux/mlx.h"

typedef struct s_data
{
	void			*mlx;
	void			*window;
	void			*img;
	char			*addr;
	int				bits_pxl;
	int				line_len;
	int				endian;
}	t_data;

/* Camera - player viewpoint */
typedef struct s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}	t_camera;

typedef struct s_world
{
	char			*tex_n; //path to textures: north
	char			*tex_s; //south
	char			*tex_w; //west
	char			*tex_e; //east
	int				ground; //ground color
	int				sky; //ceiling color
	char			**map; //map is a 2D-array
	t_camera		*cam; //define player start position and direction
}	t_world;

typedef enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall;

typedef struct s_raycaster
{
	double			time_curr; //time of current frame
	double			time_prev; //time of previous frame
	int				fps;
	t_camera		*cam;
	double			cam_x; //x-coordinate in camera space
	double			plane_x; //camera plane
	double			plane_y;
	double			ray_dir_x; //ray direction
	double			ray_dir_y;
	int				map_x; //current map cell
	int				map_y;
	double			side_dist_x; //ray length from curr pos to next x/y-side
	double			side_dist_y;
	double			delta_dist_x; //ray length from x/y-side to next x/y-side
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step; //direction to step in (+1 or -1)
	bool			hit; //wall hit control
	t_wall			wall; //which wall was hit
}	t_raycaster;

/* ============================== VALIDATION =============================== */
void	printerr_exit(char *str);
bool	check_input(int argc, char *map);
// Utils
int		ft_isspace(int c);

/* =============================== MAP DATA ================================ */

/* ============================== RENDERING ================================ */
// MLX
void	new_img(t_data *img);
// Event handlers
int		handle_keypress(int keycode, t_data *img);

/* =========================== MEMORY MANAGEMENT =========================== */
int		close_quit(t_data *img);

#endif