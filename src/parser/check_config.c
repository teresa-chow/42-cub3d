/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/30 00:10:45 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles configuration specifications */

#include "../../include/parse.h"

static void	check_specs(int fd, t_world *world);
static void	validate_lines(char *line, t_world *world, int fd);
static int	check_identifier(char *line, char *id);

void	validate_map(char *file, t_world *world)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		printerr_exit("Error\nFailed to open config file.\n", NULL);
	check_specs(fd, world);
	check_map(world, fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		printerr_exit("Error\nFailed to open config file.\n", NULL);
	save_map(world, fd);
	close(fd);
	get_player_pos(world);
	get_player_dir(world);
	format_map_lines(world);
	check_closed_map(world);
}

/* Check config specs other than map (textures and colors) */
static void	check_specs(int fd, t_world *world)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strcmp("\n", line))
			validate_lines(line, world, fd);
		else
			free(line);
		if (all_textures_set_up(world))
			break ;
		line = get_next_line(fd);
	}
	if (all_textures_set_up(world))
	{
		validate_texture(world, fd);
		convert_to_int(world, fd, 'C');
		convert_to_int(world, fd, 'F');
	}
	else
		exit_file_analyze(world, fd, "Error\n"
			"Texture identifiers missing\n", NULL);
}

/* Check color and texture identifiers */
static void	validate_lines(char *line, t_world *world, int fd)
{
	if (is_map_line(line, NULL) && !all_textures_set_up(world))
		exit_file_analyze(world, fd, "Error\n"
			"Missing identifiers\n", NULL);
	if (check_identifier(line, "NO"))
		world->tex_n = get_texture_inf(line, "NO", world, fd);
	else if (check_identifier(line, "SO"))
		world->tex_s = get_texture_inf(line, "SO", world, fd);
	else if (check_identifier(line, "WE"))
		world->tex_w = get_texture_inf(line, "WE", world, fd);
	else if (check_identifier(line, "EA"))
		world->tex_e = get_texture_inf(line, "EA", world, fd);
	else if (check_identifier(line, "F"))
		world->ground_str = get_texture_inf(line, "F", world, fd);
	else if (check_identifier(line, "C"))
		world->sky_str = get_texture_inf(line, "C", world, fd);
	else
	{
		free(line);
		exit_file_analyze(world, fd, "Error\n"
			"Spec misconfiguration\n", NULL);
	}
	free(line);
}

static int	check_identifier(char *line, char *id)
{
	int		i;
	char	*start;
	char	*end;
	char	save;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_isspace(line[i]))
		start = &line[i];
	while (line[i] && !ft_isspace(line[i]))
		i++;
	if (!line[i] || ft_isspace(line[i]))
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
