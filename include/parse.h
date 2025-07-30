/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:39:36 by tchow-so         ###   ########.fr       */
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

/* Camera - player pov:
	NORTH (N)	: -Y;
	SOUTH (S)	: +Y;
	EAST (E)	: +X;
	WEST (W)	: -X;
*/
typedef struct s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}	t_camera;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	char			*data;
	int				bits_pxl;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}	t_texture;

/* World - config info provided in *.cub */
typedef struct s_world
{
	char			*tex_n;
	char			*tex_s;
	char			*tex_w;
	char			*tex_e;
	t_texture		tex_north;
	t_texture		tex_south;
	t_texture		tex_west;
	t_texture		tex_east;
	char			*ground_str;
	int				ground;
	char			*sky_str;
	int				sky;
	int				map_len;
	int				map_wid;
	char			**map;
	char			**map_cpy;
	t_camera		*cam;
}	t_world;

/* ============================== VALIDATION =============================== */
// Command line input
bool	check_input(int argc, char *map);
// Config file checks
void	validate_map(char *file, t_world *world);
// Textures
void	validate_texture(t_world *world, int fd);
char	*get_texture_inf(char *line, char *id, t_world *world, int fd);
void	find_identifier_value(char *s, t_world *world, int fd, char *value);
int		all_textures_set_up(t_world *world);
// Colors
void	convert_to_int(t_world *world, int fd, char id);
// Map
void	check_map(t_world *world, int fd);
void	save_map(t_world *world, int fd);
void	get_player_pos(t_world *world);
void	get_player_dir(t_world *world);
void	check_closed_map(t_world *world);
char	*find_map(int fd);
void	get_player_pos(t_world *world);
void	get_player_dir(t_world *world);
void	check_valid_pos(char *line, t_world *world);
void	create_cpy_map(t_world *world);
void	format_map_lines(t_world *world);
int		is_map_line(char *s, int *player_pos);
int		char_pos_found(char *line, t_world *world);
int		flood_fill_cub(int x, int y, char **map, int high, t_world *world);

/* ================================= UTILS ================================= */
bool	check_file_format(char *str, char *format);
int		ft_isspace(int c);
size_t	strlen_newline(const char *s);

#endif