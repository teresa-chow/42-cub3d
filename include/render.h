/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/09 14:49:46 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define WIN_W 1920
# define WIN_H 1080

# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"
# include "../lib/minilibx-linux/mlx.h"
# include "parser.h"

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

typedef enum e_wall
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall;

typedef enum e_keys
{
	NONE,
	W,
	A,
	S,
	D,
	LEFT,
	RIGHT
};

typedef

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

/* ============================== RENDERING ================================ */
// MLX
void	render(t_world *world, t_data *img, t_raycaster *raycaster);
// Event handlers
int		handle_keypress(int keycode, t_data *img);

/* =========================== MEMORY MANAGEMENT =========================== */
int		close_quit(t_data *img);

#endif