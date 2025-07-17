/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/17 15:41:54 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define WIN_W 1024 //1920
# define WIN_H 576 //1080
# define BLACK 0
# define WHITE 16777215
# define GRAY 3158064
# define YELLOW 16776960
# define MAGENTA 16711935
# define PI 3.14159265358979323846

# include <X11/X.h>
# include <X11/keysym.h>
# include <sys/time.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/minilibx-linux/mlx.h"
# include "parse.h"

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

typedef struct s_dda
{
	float			spacing;
	float			x_ofs;
	float			y_ofs;
	float			x1;
	float			y1;
	float			dx;
	float			dy;
	int				step;
	float			x_inc;
	float			y_inc;
}	t_dda;

typedef enum e_wall
{
	NORTH_SOUTH,
	EAST_WEST
}	t_wall;

typedef struct s_raycaster
{
	t_data			*img;
	int				fps;
	bool			key_state[6]; // W A S D Left Right
	t_world			*world;
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
	int				step_x; // check if 2 vars needed or 1 suffice
	int				step_y;
	bool			hit; //wall hit control
	t_wall			wall; //which wall was hit
	int				line_height;
	int				line_start;
	int				line_end;
}	t_raycaster;

/* ============================== RENDERING ================================ */
// Rendering
void	launch_render_engine(t_data *img, t_world *world, t_raycaster *rc);
int		render_frame(t_raycaster *rc);
int		raycaster(t_raycaster *rc);
void	draw_minimap(t_raycaster *rc);
void	draw_minimap_grid(t_raycaster *rc, t_dda *dda);
void	draw_player(t_raycaster *rc, float spacing);
// Raycaster calculations and values (one cycle per ray)
void	calc_ray_pos_dir(t_raycaster *rc, int x);
void	reset_ray_map_coord(t_raycaster *rc);
void	calc_ray_len(t_raycaster *rc);
void	calc_step(t_raycaster *rc);
void	perform_dda(t_raycaster *rc);
void	calc_cam_dist(t_raycaster *rc);
void	calc_line_val(t_raycaster *rc);
// Calculate player position and direction
void	calc_player_movement(t_raycaster *rc);
void	calc_player_rotation(t_raycaster *rc);
// Event handlers
int		handle_keypress(int keycode, t_raycaster *rc);
int		handle_keyrelease(int keycode, t_raycaster *rc);
// Time management
void	get_time_ms(unsigned int *curr_time);
// Graphics
void	fill_background(t_raycaster *rc);
void	pixel_put(t_data *img, int x, int y, int color);

/* =========================== MEMORY MANAGEMENT =========================== */
int		close_quit(t_raycaster *rc);

#endif
