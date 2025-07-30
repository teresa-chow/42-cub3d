/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:59:32 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/30 11:32:25 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration errors */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	check_map_content(t_world *world, int fd, char *line);
static void	calc_map_dimensions(t_world *world, char *line);
static void	check_map_placement(t_world *world, int fd);

void	check_map(t_world *world, int fd)
{
	char	*line;

	line = find_map(fd);
	check_map_content(world, fd, line);
	check_map_placement(world, fd);
}

static void	check_map_content(t_world *world, int fd, char *line)
{
	bool	in_map;
	int		player_pos;

	player_pos = 0;
	in_map = false;
	while (line)
	{
		calc_map_dimensions(world, line);
		if (!in_map && is_map_line(line, &player_pos))
			in_map = true;
		else if (!is_map_line(line, &player_pos))
			exit_file_analyze(world, fd, "Error\n"
				"Invalid map\n", NULL);
		if (player_pos > 1)
			exit_file_analyze(world, fd, "Error\n"
				"Multiple player positions\n", NULL);
		free(line);
		line = get_next_line(fd);
		if (line && !ft_strcmp("\n", line) && in_map)
			break ;
	}
	free(line);
	if (!player_pos)
		exit_file_analyze(world, fd, "Error\n"
			"Missing player position\n", NULL);
}

static void	calc_map_dimensions(t_world *world, char *line)
{
	if (strlen_newline(line) > (size_t)world->map_wid)
		world->map_wid = strlen_newline(line);
	world->map_len++;
}

static void	check_map_placement(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			exit_file_analyze(world, fd, "Error\n"
				"Map content misconfiguration\n", NULL);
		free(line);
		line = get_next_line(fd);
	}
}
