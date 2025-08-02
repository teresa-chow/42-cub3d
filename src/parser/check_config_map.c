/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:59:32 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/02 10:59:02 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration errors */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	check_map_content(char **line, t_world *world, int fd);
static void	calc_map_dimensions(t_world *world, char *line);
static void	check_map_placement(char **line, t_world *world, int fd);

void	check_map(char **line, t_world *world, int fd)
{
	find_map(line, fd);
	check_map_content(line, world, fd);
	check_map_placement(line, world, fd);
}

static void	check_map_content(char **line, t_world *world, int fd) // no. lines
{
	bool	in_map;
	int		player_pos;

	player_pos = 0;
	in_map = false;
	while (*line)
	{
		calc_map_dimensions(world, *line);
		if (!in_map && is_map_line(*line, &player_pos))
			in_map = true;
		else if (!is_map_line(*line, &player_pos))
		{
			free(*line);
			exit_on_error(world, fd, MAP_INVALID);
		}
		if (player_pos > 1)
		{
			free(*line);
			exit_on_error(world, fd, PLAYER_POS_EXTRA);
		}
		free(*line);
		*line = get_next_line(fd);
		if (*line && !ft_strcmp("\n", *line) && in_map)
			break ;
	}
	free(*line);
	if (!player_pos)
		exit_on_error(world, fd, PLAYER_POS_NONE);
}

static void	calc_map_dimensions(t_world *world, char *line)
{
	if (strlen_newline(line) > (size_t)world->map_wid)
		world->map_wid = strlen_newline(line);
	world->map_len++;
}

static void	check_map_placement(char **line, t_world *world, int fd)
{
	*line = get_next_line(fd);
	while (*line)
	{
		if (ft_strcmp(*line, "\n"))
		{
			free(*line);
			exit_on_error(world, fd, MAP_INVALID);
		}
		free(*line);
		*line = get_next_line(fd);
	}
}

void	check_closed_map(t_world *world)
{
	char	**map_copy;
	int		i;
	int		j;

	map_copy = map_dup(world);
	if (!map_copy)
		exit_on_error(world, -1, MEMALLOC);
	i = -1;
	j = -1;
	while (map_copy[++i])
	{
		while (map_copy[i][++j])
		{
			if (map_copy[i][j] == '0' || map_copy[i][j] == 'N'
			|| map_copy[i][j] == 'S' || map_copy[i][j] == 'E'
			|| map_copy[i][j] == 'W')
				flood_fill_cub(j, i, map_copy, world);
		}
		j = -1;
	}
	free_map(map_copy, world->map_len);
}
