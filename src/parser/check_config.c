/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/02 11:09:03 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles configuration specifications */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	check_specs(char **line, int fd, t_world *world);
static void	validate_lines(char **line, t_world *world, int fd);
static void	check_missing_identifier(t_world *world, int fd);
static int	check_identifier(char *line, char *id);

void	validate_map(char *file, t_world *world)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(CONFIG_OPEN);
		exit(EXIT_FAILURE);
	}
	check_specs(&line, fd, world);
	check_map(&line, world, fd);
	close(fd);
	get_map_data(file, world);
	check_closed_map(world);
}

/* Check config specs other than map (textures and colors) */
static void	check_specs(char **line, int fd, t_world *world)
{
	*line = get_next_line(fd);
	while (*line)
	{
		if (ft_strcmp("\n", *line))
			validate_lines(line, world, fd);
		free(*line);
		*line = get_next_line(fd);
	}
	if (all_textures_set_up(world))
	{
		validate_texture(world, fd);
		convert_to_int(world, fd, 'C');
		convert_to_int(world, fd, 'F');
	}
	else
		check_missing_identifier(world, fd);
}

/* Check color and texture identifiers */
static void	validate_lines(char **line, t_world *world, int fd)
{
	if (is_map_line(*line, NULL) && !all_textures_set_up(world))
	{
		free(*line);
		exit_on_error(world, fd, SPEC_INVALID); // "Missing identifiers"
	}
	if (check_identifier(*line, "NO"))
		world->tex_n = get_texture_inf(*line, "NO", world, fd);
	else if (check_identifier(*line, "SO"))
		world->tex_s = get_texture_inf(*line, "SO", world, fd);
	else if (check_identifier(*line, "WE"))
		world->tex_w = get_texture_inf(*line, "WE", world, fd);
	else if (check_identifier(*line, "EA"))
		world->tex_e = get_texture_inf(*line, "EA", world, fd);
	else if (check_identifier(*line, "F"))
		world->ground_str = get_texture_inf(*line, "F", world, fd);
	else if (check_identifier(*line, "C"))
		world->sky_str = get_texture_inf(*line, "C", world, fd);
	else
	{
		free(*line);
		exit_on_error(world, fd, SPEC_INVALID);
	}
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

static void	check_missing_identifier(t_world *world, int fd)
{
	if (!world->tex_n || !world->tex_s || !world->tex_e || !world->tex_w)
		exit_on_error(world, fd, TEX_MISSING);
	else if (!world->sky_str || !world->ground_str)
		exit_on_error(world, fd, COLOR_MISSING);
}
