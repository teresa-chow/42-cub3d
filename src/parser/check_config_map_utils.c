/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:09:43 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/01 16:38:54 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

/* Get lines until have a filled line after the texts*/
char	*find_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (!ft_strcmp("\n", line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

/* Check if is a valid map line */
int	is_map_line(char *s, int *player_pos)
{
	while (*s)
	{
		if (*s != '1' && *s != '0' && *s != 'N' && *s != 'S'
			&& *s != 'E' && *s != 'W' && *s != '\n' && *s != ' ')
			return (0);
		if (player_pos && (*s == 'N' || *s == 'S'
				|| *s == 'E' || *s == 'W'))
			(*player_pos)++;
		s++;
	}
	return (1);
}

void	check_valid_pos(t_world *world)
{
	int	y;
	int	x;

	y = world->cam->pos_y;
	x = world->cam->pos_x;
	if (y == 0 || y == world->map_len || x == 0 || x == world->map_wid)
		exit_on_error(world, -1, PLAYER_POS_INVALID);
	if ((world->map[y - 1][x] != '0' && world->map[y - 1][x] != '1')
		|| (world->map[y + 1][x] != '0' && world->map[y + 1][x] != '1')
		|| (world->map[y][x - 1] != '0' && world->map[y][x - 1] != '1')
		|| (world->map[y][x + 1] != '0' && world->map[y][x + 1] != '1'))
		exit_on_error(world, -1, PLAYER_POS_INVALID);
}

int	pos_found(int y, t_world *world)
{
	int	x;

	x = 0;
	while (world->map[y][x])
	{
		if (world->map[y][x] == 'N' || world->map[y][x] == 'S'
			|| world->map[y][x] == 'W' || world->map[y][x] == 'E')
		{
			world->cam->pos_x = x;
			return (1);
		}
		x++;
	}
	return (0);
}

int	flood_fill_cub(int x, int y, char **map, t_world *world)
{
	if (x < 0 || y < 0
		|| (size_t)x >= ft_strlen(map[y])
		|| y >= world->map_len
		|| ft_isspace(map[y][x]))
		exit_on_error(world, -1, MAP_OPEN);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	map[y][x] = 'x';
	flood_fill_cub(x + 1, y, map, world);
	flood_fill_cub(x - 1, y, map, world);
	flood_fill_cub(x, y - 1, map, world);
	flood_fill_cub(x, y + 1, map, world);
	return (0);
}
