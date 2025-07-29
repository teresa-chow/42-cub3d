/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:24:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 00:36:40 by tchow-so         ###   ########.fr       */
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
			&& !ft_strstr(line, "F") && !ft_strstr(line, "C")
			&& ft_strcmp("\n", line))
			break ;
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
		exit_file_analyze(world, fd, "Error\n"
			"Memory allocation failed\n", NULL);
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
	int		y;
	char	**map;

	y = -1;
	map = world->map;
	world->cam = ft_calloc(sizeof(t_camera), sizeof(char));
	if (!world->cam)
		exit_file_analyze(world, 0, "Error\nMemory allocation failed\n", NULL);
	while (map[++y])
	{
		if (char_pos_found(map[y], world))
		{
			world->cam->pos_y = y;
			check_valid_pos(map[y], world);
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

void	check_closed_map(t_world *world)
{
	char	**map_cpy;
	int		i;
	int		j;

	world->map_cpy = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!world->map_cpy)
		exit_file_analyze(world, 0, "Error\nMemory allocation failed\n", NULL);
	create_cpy_map(world);
	map_cpy = world->map_cpy;
	i = -1;
	j = -1;
	while (map_cpy[++i])
	{
		while (map_cpy[i][++j])
		{
			if (map_cpy[i][j] == '0' || map_cpy[i][j] == 'N'
			|| map_cpy[i][j] == 'S' || map_cpy[i][j] == 'E'
			|| map_cpy[i][j] == 'W')
				flood_fill_cub(j, i, map_cpy, world->map_len, world);
		}
		j = -1;
	}
	free_map(world->map_cpy, world->map_len);
}
