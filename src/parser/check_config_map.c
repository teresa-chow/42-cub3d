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

static void	check_map_content(t_tmp *tmp, t_world *world, int fd);
static void	calc_map_dimensions(t_world *world, char *line);
static void	check_map_placement(t_tmp *tmp, t_world *world, int fd);

void	check_map(t_tmp *tmp, t_world *world, int fd)
{
	check_map_content(tmp, world, fd);
	check_map_placement(tmp, world, fd);
}

static void	check_map_content(t_tmp *tmp, t_world *world, int fd) // no. lines
{
	bool	in_map;
	int		player_pos;

	player_pos = 0;
	in_map = false;
	while (tmp->line)
	{
		calc_map_dimensions(world, tmp->line);
		if (!in_map && is_map_line(tmp->line, &player_pos))
			in_map = true;
		else if (!is_map_line(tmp->line, &player_pos))
			exit_on_error(world, fd, MAP_INVALID, tmp);
		if (player_pos > 1)
			exit_on_error(world, fd, PLAYER_POS_EXTRA, tmp);
		free(tmp->line);
		tmp->line = get_next_line(fd, tmp);
		if (tmp->line && !ft_strcmp("\n", tmp->line) && in_map)
			break ;
	}
	free(tmp->line);
	tmp->line = NULL;
	if (!player_pos)
		exit_on_error(world, fd, PLAYER_POS_NONE, tmp);
}


static void	calc_map_dimensions(t_world *world, char *line)
{
	if (strlen_newline(line) > (size_t)world->map_wid)
		world->map_wid = strlen_newline(line);
	world->map_len++;
}

static void	check_map_placement(t_tmp *tmp, t_world *world, int fd)
{
	tmp->line = get_next_line(fd, tmp);
	while (tmp->line)
	{
		if (ft_strcmp(tmp->line, "\n"))
			exit_on_error(world, fd, MAP_EXTRA, tmp);
		free(tmp->line);
		tmp->line = get_next_line(fd, tmp);
	}
}

void	check_closed_map(t_world *world, t_tmp *tmp)
{
	int		i;
	int		j;

	tmp->map_cpy = map_dup(world, tmp);
	if (!tmp->map_cpy)
		exit_on_error(world, -1, MEMALLOC, tmp);
	i = -1;
	j = -1;
	while (tmp->map_cpy[++i])
	{
		while (tmp->map_cpy[i][++j])
		{
			if (tmp->map_cpy[i][j] == '0' || tmp->map_cpy[i][j] == 'N'
			|| tmp->map_cpy[i][j] == 'S' || tmp->map_cpy[i][j] == 'E'
			|| tmp->map_cpy[i][j] == 'W')
				flood_fill_cub(j, i, world, tmp);
		}
		j = -1;
	}
	free_map(tmp->map_cpy, world->map_len);
}
