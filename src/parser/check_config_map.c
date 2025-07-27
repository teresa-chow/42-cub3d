/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:59:32 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/27 23:00:34 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration errors */

#include "../../include/parse.h"

static void	check_map_content(t_world *world, int fd);
static void	check_map_line(char *s, int fd, t_world *world);
static void	check_map_placement(t_world *world, int fd);

void	check_map(t_world *world, int fd)
{
	check_map_content(world, fd);
	check_map_placement(world, fd);
}

static void	check_map_content(t_world *world, int fd)
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
				check_map_line(line, fd, world);
		}
		free(line);
		line = get_next_line(fd);
	}
	/*if (!world->pos_find)
		exit_file_analyze(world, fd, "Error\nNo positions found\n");*/
}

static void	check_map_line(char *s, int fd, t_world *world)
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

static void	check_map_placement(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			exit_file_analyze(world, fd, "Error\n"
				"Map content misconfiguration.\n");
	}
}
