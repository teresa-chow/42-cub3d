/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:59:32 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/26 06:32:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration errors */

#include "../../include/parse.h"

static void	start_saving(t_world *world, int fd, char *line);

void	analyze_line(char *s, int fd, t_world *world)
{
	while (*s)
	{
		if (*s != '1' && *s != '0' && *s != 'N' && *s != 'S' 
			&& *s != 'E' && *s != 'W' && *s != '\n' && *s != ' ')
			exit_file_analyze(world, fd, "Error\nMap with invalid information!\n");
		/*if (!world->pos_find && *s != '1' && *s != '0' && *s != '\n' && *s != ' ')
			world->pos_find = true;
		else if (world->pos_find && *s != '1' && *s != '0' && *s != '\n' && *s != ' ')
			exit_file_analyze(world, fd, "Error\nMore than a found position!\n");*/
		s++;
	}
}

void	analyze_map_info(t_world *world, int fd)
{
	char	*line;
	bool	in_map;

	in_map = false;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strcmp(line, "\n") && in_map)
		{
			free(line);
			break;
		}
		else if (ft_strcmp(line, "\n") && !in_map)
			in_map = true;
		if (ft_strlen(line) > (size_t)world->map_wid)
			world->map_wid = ft_strlen(line);
		if (ft_strcmp(line, "\n"))
		{
			world->map_len++;
			analyze_line(line, fd, world);
		}
		free(line);
		line = get_next_line(fd);
	}
	/*if (!world->pos_find)
		exit_file_analyze(world, fd, "Error\nNo positions found\n");*/
}

void	save_map(t_world *world, char *file)
{
	int	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_file_analyze(world, fd, "cub3D: map opening failed\n");
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
		exit_file_analyze(world, fd, "Error\nMemory Allocation!\n");
	i = 0;
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			world->map[i] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
}
