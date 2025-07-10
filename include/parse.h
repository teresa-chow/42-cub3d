/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:28:45 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/10 09:51:26 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdlib.h>
# include <stdbool.h>
# include "../lib/libft/libft/libft.h"
# include "../lib/libft/ft_printf/ft_printf.h"
# include "../lib/libft/get_next_line/get_next_line.h"

/* Camera - player viewpoint */
typedef struct s_camera
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
}	t_camera;

/* World - config info privided in *.cub */
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

/* ============================== VALIDATION =============================== */
bool	check_input(int argc, char *map);
// Utils
int		ft_isspace(int c);
void	printerr_exit(char *str);

/* =============================== MAP DATA ================================ */

#endif