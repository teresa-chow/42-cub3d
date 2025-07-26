/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/26 07:01:25 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
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
void	validate_map(char *file, t_world *world);
// Textures
void    validate_texture(t_world *world, int fd);
char	*get_texture_inf(char *line, char *id);
// Colors
void	convert_to_int(t_world *world, int fd, char id);
// Map
void	analyze_line(char *s, int fd, t_world *world);
void	analyze_map_info(t_world *world, int fd);
void	save_map(t_world *world, char *file);

/* ======================= DYNAMIC MEMORY MANAGEMENT ======================= */
void	free_world(t_world *world);

/* ============================= ERROR HANDLING ============================ */
void	exit_file_analyze(t_world *world, int fd, char *msg);
void	printerr_exit(char *str);

/* ================================= UTILS ================================= */
bool	check_file_format(char *str, char *format);
int		ft_isspace(int c);

#endif