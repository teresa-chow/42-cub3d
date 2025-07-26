/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/26 07:28:56 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles configuration specifications */

#include "../../include/parse.h"

static void	check_first_data(int fd, t_world *world);
static void	check_other_inf(t_world *world, int fd);
static void	validate_lines(char *line, t_world *world, int fd);
static int	check_identifier(char *line, char *id);

void	validate_map(char *file, t_world *world)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		printerr_exit("Error\nFailed to open config file.\n");
	check_first_data(fd, world);
	analyze_map_info(world, fd);
	check_other_inf(world, fd);
	close(fd);
	save_map(world, file);

	close(fd); // close second time this file because i reopened
}

/* Check config specs other than map */
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
    validate_texture(world, fd);
	convert_to_int(world, fd, 'C');
	convert_to_int(world, fd, 'F');
}

static void	check_other_inf(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp(line, "\n"))
			exit_file_analyze(world, fd, "Error\n"
				"Map should be the last information!\n");
	}
}

/* Check color and texture identifiers */
static void	validate_lines(char *line, t_world *world, int fd)
{
	if (ft_strcmp(line, "\n"))
	{
		if (!world->tex_n && check_identifier(line, "NO"))
			world->tex_n = get_texture_inf(line, "NO");
		else if (!world->tex_s && check_identifier(line, "SO"))
			world->tex_s = get_texture_inf(line, "SO");
		else if (!world->tex_w && check_identifier(line, "WE"))
			world->tex_w = get_texture_inf(line, "WE");
		else if (!world->tex_e && check_identifier(line, "EA"))
			world->tex_e = get_texture_inf(line, "EA");
		else if (!world->ground_str && check_identifier(line, "F"))
			world->ground_str =  get_texture_inf(line, "F");
		else if (!world->sky_str && check_identifier(line, "C"))
			world->sky_str = get_texture_inf(line, "C");
		else
			exit_file_analyze(world, fd, "Error\n"
				"Color or texture misconfiguration.\n");
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
