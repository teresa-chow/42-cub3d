/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:24:50 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/27 23:05:55 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles map configuration value */

#include "../../include/parse.h"

static void	start_saving(t_world *world, int fd, char *line);

void	save_map(t_world *world, char *file)
{
	int	fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_file_analyze(world, fd, "Error\nFailed to open config file.\n");
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
    //fix: i is not incremented
}