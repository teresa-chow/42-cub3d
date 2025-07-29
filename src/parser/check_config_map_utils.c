/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 11:09:43 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/29 12:01:38 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

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

void	check_valid_pos(char *line, t_world *world)
{
	int	len;
	int	sub;

	sub = 1;
	len = ft_strlen(line);
	if (line[len - 1] == '\n')
		sub = 2;
	if (world->cam->pos_x == 0 || world->cam->pos_x == len - sub ||
	world->cam->pos_y == 0 || world->cam->pos_y == world->map_len - 1)
		exit_file_analyze(world, 0, "Error\nWrong player position!\n", NULL);
}

int	char_pos_found(char *line, t_world *world)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i]))
		{
			world->cam->pos_x = i;
			return (1);
		}
	}
	return (0);
}

int	flood_fill_cub(int x, int y, char **map, int high, t_world *world)
{
	if (x < 0 || y < 0 || (size_t)x >= ft_strlen(map[y]) || y >= high)
		exit_file_analyze(world, 0, "Error\nMap not closed\n", NULL);
	if (ft_isspace(map[y][x]))
		exit_file_analyze(world, 0, "Error\nMap not closed\n", NULL);
	if (map[y][x] == '1' || map[y][x] == 'x')
		return (0);
	map[y][x] = 'x';
	flood_fill_cub(x + 1, y, map, high, world);
	flood_fill_cub(x - 1, y, map, high, world);
	flood_fill_cub(x, y - 1, map, high, world);
	flood_fill_cub(x, y + 1, map, high, world);
	return (0);
}