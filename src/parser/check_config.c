/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/25 17:34:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles configuration specifications */

#include "../../include/parse.h"

static void	check_first_data(int fd, t_world *world);
static void	validate_lines(char *line, t_world *world, int fd);
static int	check_identifier(char *line, char *id);

void	validate_map(char *file, t_world *world)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		printerr_exit("cub3D: failed to open config file\n");
	check_first_data(fd, world);
	close(fd);
}

/* Check config other than map */
static void	check_first_data(int fd, t_world *world)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		validate_lines(line, world, fd);
		if (world->tex_n && world->tex_s && world->tex_e 
			&& world->tex_w && world->sky_str && world->ground_str)
			break;
		free(line);
		line = get_next_line(fd);
	}
        validate_texture_path_and_format(world, fd);
	convert_to_int(world, fd, 'C');
	convert_to_int(world, fd, 'F');
	// create_and_analyze_map(world);
}

/* Check color and texture identifiers */
static void	validate_lines(char *line, t_world *world, int fd)
{
	if (ft_strcmp(line, "\n"))
	{
		if (check_identifier(line, "NO"))
			world->tex_n = get_texture_inf(line, "NO");
		else if (check_identifier(line, "SO"))
			world->tex_s = get_texture_inf(line, "SO");
		else if (check_identifier(line, "WE"))
			world->tex_w = get_texture_inf(line, "WE");
		else if (check_identifier(line, "EA"))
			world->tex_e = get_texture_inf(line, "EA");
		else if (check_identifier(line, "F"))
			world->ground_str =  get_texture_inf(line, "F");
		else if (check_identifier(line, "C"))
			world->sky_str = get_texture_inf(line, "C");
		else
			exit_file_analyze(world, fd, "Wrong format or "
				"identifier provided.\n");
	}
}

static int	check_identifier(char *line, char *id)
{
		int     i;
		char    *start;
		char    *end;
		char    save;

		i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_isspace(line[i]))
		start = &line[i];
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isspace(line[i]))
	{
		end = &line[i];
		save = *end;
		*end = 0;
		if (!ft_strcmp(start, id))
		{
			*end = save;
			return (1);
		}
		*end = save;
	}
	return (0);
}
