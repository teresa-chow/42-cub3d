/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/25 12:26:41 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdbool.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"

/* Camera - player viewpoint: */
/*
	NORTH : -Y dir_x = 0 dir_y = -1;
	SOUTH : +Y;
	EAST : +X;
	WEST : -X;
*/
typedef struct s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}	t_camera;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	color;
}	t_rgb;

/* World - config info provided in *.cub */
typedef struct s_world
{
	char			*tex_n; //path to textures: north
	char			*tex_s; //south
	char			*tex_w; //west
	char			*tex_e; //east
	char			*ground_str;
	int				ground; //ground color
	char			*sky_str;
	int				sky; //ceiling color
	int				map_len;
	int				map_wid;
	char			**map; //map is a 2D-array
	t_camera		*cam; //define player start position and direction
}	t_world;

/* ============================== VALIDATION =============================== */
// Command line input
bool	check_input(int argc, char *map);
// Config file checks
void	check_file(char *file, t_world *world);
void    exit_file_analyze(t_world *world, int fd, char *msg);
int		check_identifier(char *line, char *id);
// Textures
char	*get_texture_inf(char *line, char *id);

/* ================================= UTILS ================================= */
// Memory management
void	free_world(t_world *world);
// Utils
int		ft_isspace(int c);
void	printerr_exit(char *str);

#endif