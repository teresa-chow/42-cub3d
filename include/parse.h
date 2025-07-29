/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/29 11:53:33 by carlaugu         ###   ########.fr       */
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
	NORTH (N) : -Y dir_x = 0 dir_y = -1;
	SOUTH (S) : +Y dir_x = 0 dir_y = 1;
	EAST (E): +X dir_x = 1 dir_y = 0;
	WEST (W): -X dir_x = -1 dir_y = 0;
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
	char			**map_cpy;
	t_camera		*cam; //define player start position and direction
}	t_world;

/* ============================== VALIDATION =============================== */
// Command line input
bool	check_input(int argc, char *map);
// Config file checks
void	validate_map(char *file, t_world *world);
// Textures
void    validate_texture(t_world *world, int fd);
char	*get_texture_inf(char *line, char *id, t_world *world, int fd);
// Colors
void	convert_to_int(t_world *world, int fd, char id);
// Map
void	check_map(t_world *world, int fd);
void	save_map(t_world *world, int fd);
void	get_player_pos(t_world *world);
void	get_player_dir(t_world *world);
void	check_closed_map(t_world *world);

/* ======================= DYNAMIC MEMORY MANAGEMENT ======================= */
void	free_world(t_world *world);
void	free_numbers(char **numbers);
void	free_map(char **map, int len);

/* ============================= ERROR HANDLING ============================ */
void	exit_file_analyze(t_world *world, int fd, char *msg, char *value);
void	printerr_exit(char *str, char *id);

/* ================================= UTILS ================================= */
bool	check_file_format(char *str, char *format);
int		ft_isspace(int c);
//textures utils
void	find_identifier_value(char *s, t_world *world, int fd, char *value);
int		all_textures_set_up(t_world *world);
//map utils
char	*find_map(int fd);
void	get_player_pos(t_world *world);
void	get_player_dir(t_world *world);
void	check_valid_pos(char *line, t_world *world);
void	create_cpy_map(t_world *world);
int		is_map_line(char *s, int *player_pos);
int		char_pos_found(char *line, t_world *world);
int		flood_fill_cub(int x, int y, char **map, int high, t_world *world);

#endif