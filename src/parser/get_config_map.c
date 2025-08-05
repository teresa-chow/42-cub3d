/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:24:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/05 16:25:22 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration value */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	fill_map_content(t_world *world, int fd, t_tmp *tmp);

void	get_map_data(char *file, t_world *world, t_tmp *tmp)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(CONFIG_OPEN);
		exit(EXIT_FAILURE);
	}
	get_map_content(world, tmp, fd);
	close(fd);
	get_player_pos(world, tmp);
	get_player_dir(world);
	zero_player_pos_map(world);
}

void	get_map_content(t_world *world, t_tmp *tmp, int fd)
{
	tmp->line = get_next_line(fd, tmp);
	while (tmp->line)
	{
		if (!ft_strstr(tmp->line, "NO") && !ft_strstr(tmp->line, "SO")
			&& !ft_strstr(tmp->line, "WE") && !ft_strstr(tmp->line, "EA")
			&& !ft_strstr(tmp->line, "F") && !ft_strstr(tmp->line, "C")
			&& ft_strcmp("\n", tmp->line))
			break ;
		free(tmp->line);
		tmp->line = get_next_line(fd, tmp);
	}
	fill_map_content(world, fd, tmp);
}

static void	fill_map_content(t_world *world, int fd, t_tmp *tmp)
{
	int	i;
	int	j;

	world->map = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!world->map)
		exit_on_error(world, fd, MEMALLOC, tmp);
	j = 0;
	while (tmp->line)
	{
		i = 0;
		if (tmp->line[i] && tmp->line[i] != '\n')
			world->map[j] = ft_calloc(world->map_wid + 1, sizeof(char));
		while (tmp->line[i] && tmp->line[i] != '\n')
		{
			world->map[j][i] = tmp->line[i];
			i++;
		}
		j++;
		free(tmp->line);
		tmp->line = get_next_line(fd, tmp);
	}
}

void	get_player_pos(t_world *world, t_tmp *tmp)
{
	int		y;

	y = -1;
	world->cam = ft_calloc(sizeof(t_camera), sizeof(char));
	if (!world->cam)
		exit_on_error(world, -1, MEMALLOC, tmp);
	while (world->map[++y])
	{
		if (pos_found(y, world))
		{
			world->cam->pos_y = y;
			check_valid_pos(world, tmp);
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
