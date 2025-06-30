/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/06/30 16:29:53 by tchow-so         ###   ########.fr       */
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
	int				map_len;
	int				map_wid;
	char			*addr;
	int				bits_pxl;
	int				line_len;
	int				endian;
}	t_data;

typedef struct s_img
{
	/* data */
}	t_img;

typedef struct s_map
{
	char	*tex_n; //path to textures: north
	char	*tex_s; //south
	char	*tex_w; //west
	char	*tex_e; //east
	int		ground; //ground color
	int		sky; //ceiling color
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct	s_plane
{
	double  x;
    double  y;
}	t_plane;

typedef struct s_game
{
	struct s_player	player;
	struct s_plane	camera;
}	t_game;

/* ============================== VALIDATION =============================== */
void	printerr_exit(char *str);
bool	check_input(int argc, char *argv);
// Utils
int		ft_isspace(int c);

/* =============================== MAP DATA ================================ */


/* ============================== RENDERING ================================ */
// MLX
void	new_img(t_data *img);
// Event handlers
int		handle_keypress(int keycode, t_data *img);

/* =========================== MEMORY MANAGEMENT =========================== */
int	    close_quit(t_data *img);

#endif