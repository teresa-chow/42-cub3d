/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:24:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/31 11:23:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration value */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	fill_map_content(t_world *world, int fd, char *line);

void	get_map_content(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strstr(line, "NO") && !ft_strstr(line, "SO")
			&& !ft_strstr(line, "WE") && !ft_strstr(line, "EA")
			&& !ft_strstr(line, "F") && !ft_strstr(line, "C")
			&& ft_strcmp("\n", line))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	fill_map_content(world, fd, line);
}

static void	fill_map_content(t_world *world, int fd, char *line)
{
	int	i;
	int	j;

	world->map = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!world->map)
		exit_file_analyze(world, fd, "Error\n"
			"Memory allocation failed\n", NULL);
	j = 0;
	while (line)
	{
		i = 0;
		if (line[i])
			world->map[j] = ft_calloc(world->map_wid + 1, sizeof(char));
		while (line[i] && line[i] != '\n')
		{
			world->map[j][i] = line[i];
			i++;
		}
		j++;
		free(line);
		line = get_next_line(fd);
	}
}

void	get_player_pos(t_world *world)
{
	int		y;
	//char	**map;

	y = 0;
	//map = world->map;
	world->cam = ft_calloc(sizeof(t_camera), sizeof(char));
	if (!world->cam)
		exit_file_analyze(world, 0, "Error\nMemory allocation failed\n", NULL);
	while (world->map[y++])
	{
		if (pos_found(y, world))
		{
			world->cam->pos_y = y;
			check_valid_pos(world);
			break ;
		}
	}
}

void	get_player_dir(t_world *world)
{
	char		**map;
	t_camera	*cam;

	map = world->map;
	cam = world->cam;
	if (map[(int)cam->pos_y][(int)cam->pos_x] == 'N')
	{
		world->cam->dir_x = 0;
		world->cam->dir_y = -1;
	}
	else if (map[(int)cam->pos_y][(int)cam->pos_x] == 'S')
	{
		world->cam->dir_x = 0;
		world->cam->dir_y = 1;
	}
	else if (map[(int)cam->pos_y][(int)cam->pos_x] == 'E')
	{
		world->cam->dir_x = 1;
		world->cam->dir_y = 0;
	}
	else if (map[(int)cam->pos_y][(int)cam->pos_x] == 'W')
	{
		world->cam->dir_x = -1;
		world->cam->dir_y = 0;
	}
}

void	zero_player_pos_map(t_world *world)
{
	int		y;
	int		x;

	y = 0;
	while (y < world->map_len)
	{
		x = 0;
		while (world->map[y][x])
		{
			if (world->map[y][x] == 'N' || world->map[y][x] == 'S'
			|| world->map[y][x] == 'E' || world->map[y][x] == 'W')
				world->map[y][x] = '0';
			x++;
		}
		y++;
	}
}
