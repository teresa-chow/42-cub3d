/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:09:43 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/06 10:22:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

/* Check if is a valid map line */
int	is_map_line(char *s, int *player_pos)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W' && s[i] != '\n' && s[i] != ' ')
			return (0);
		if (player_pos && (s[i] == 'N' || s[i] == 'S'
				|| s[i] == 'E' || s[i] == 'W'))
			(*player_pos)++;
		i++;
	}
	return (1);
}

void	check_valid_pos(t_world *world, t_tmp *tmp)
{
	int	y;
	int	x;

	y = world->cam->pos_y;
	x = world->cam->pos_x;
	if (y == 0 || y == world->map_len || x == 0 || x == world->map_wid)
		exit_on_error(world, -1, PLAYER_POS_INVALID, tmp);
	if ((world->map[y - 1][x] != '0' && world->map[y - 1][x] != '1')
		|| (world->map[y + 1][x] != '0' && world->map[y + 1][x] != '1')
		|| (world->map[y][x - 1] != '0' && world->map[y][x - 1] != '1')
		|| (world->map[y][x + 1] != '0' && world->map[y][x + 1] != '1'))
		exit_on_error(world, -1, PLAYER_POS_INVALID, tmp);
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

/*int	flood_fill_cub(int x, int y, t_world *world, t_tmp *tmp)
{
	char	**map;

	map = tmp->map_cpy;
	if (x < 0 || y < 0
		|| (size_t)x >= ft_strlen(map[y])
		|| y >= world->map_len
		|| ft_isspace(map[y][x]))
		exit_on_error(world, -1, MAP_OPEN, tmp);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	map[y][x] = 'x';
	flood_fill_cub(x + 1, y, world, tmp);
	flood_fill_cub(x - 1, y, world, tmp);
	flood_fill_cub(x, y - 1, world, tmp);
	flood_fill_cub(x, y + 1, world, tmp);
	return (0);
}*/
