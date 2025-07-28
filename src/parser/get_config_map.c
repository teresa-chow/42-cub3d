/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:24:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/26 09:43:29 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration value */

#include "../../include/parse.h"

static void	start_saving(t_world *world, int fd, char *line);

void	save_map(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strstr(line, "NO") && !ft_strstr(line, "SO")
		&& !ft_strstr(line, "WE") && !ft_strstr(line, "EA")
		&& !ft_strstr(line, "F") && !ft_strstr(line, "C") && ft_strcmp("\n", line))
			break;
		free(line);
		line = get_next_line(fd);
	}
	start_saving(world, fd, line);
}

static void	start_saving(t_world *world, int fd, char *line)
{
	int	i;

	world->map = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!world->map)
		exit_file_analyze(world, fd, "Error\nMemory Allocation!\n", NULL);
	i = -1;
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			world->map[++i] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
}

void	get_player_pos(t_world *world)
{
	int	y;
	char	**map;

	y = -1;
	map = world->map;
	world->cam = ft_calloc(sizeof(t_camera), sizeof(char));
	if (!world->cam)
		exit_file_analyze(world, 0, "Error\nMemory Allocation!\n", NULL);
	while (map[++y])
	{
		if (char_pos_found(map[y], world))
		{
			world->cam->pos_y = y;
			check_valid_pos(map[y], world);
			break;
		}
	}
}

void	get_player_dir(t_world *world)
{
	char	**map;
	t_camera	*cam;

	map = world->map;
	cam = world->cam;
	if (map[cam->pos_y][cam->pos_x] == 'N')
	{
		world->cam->dir_x = 0;
		world->cam->dir_y = -1;
	}
	else if (map[cam->pos_y][cam->pos_x] == 'S')
	{
		world->cam->dir_x = 0;
		world->cam->dir_y = 1;
	}
	else if (map[cam->pos_y][cam->pos_x] == 'E')
	{
		world->cam->dir_x = 1;
		world->cam->dir_y = 0;
	}
	else if (map[cam->pos_y][cam->pos_x] == 'W')
	{
		world->cam->dir_x = -1;
		world->cam->dir_y = 0;
	}
}

void	check_closed_map(t_world *world)
{
	char	**map_cpy;
	int	i;

	world->map_cpy = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!world->map_cpy)
		exit_file_analyze(world, 0, "Error\nMemory allocation\n", NULL);
	i = -1;
	while (++i < world->map_len)
	{
		world->map_cpy[i] = ft_substr(world->map[i], 0, ft_strlen(world->map[i]));
		if (!world->map_cpy[i])
			exit_file_analyze(world, 0, "Error\nMemory allocation\n", NULL);
	}
	map_cpy = world->map_cpy;
	flood_fill_cub(world->cam->pos_x,world->cam->pos_y, map_cpy, world->map_len, world);
	free_map(world->map_cpy, world->map_len);
}
