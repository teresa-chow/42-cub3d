/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/02 11:31:52 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles configuration specifications */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	check_specs(int fd, t_world *world, t_tmp *tmp);
static void	validate_lines(t_world *world, int fd, t_tmp *tmp);
static int	check_identifier(char *line, char *id);

void	validate_map(char *file, t_world *world)
{
	int		fd;
	t_tmp	tmp;

	ft_bzero(&tmp, sizeof(tmp));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(CONFIG_OPEN);
		exit(EXIT_FAILURE);
	}
	check_specs(fd, world, &tmp);
	check_map(&tmp, world, fd);
	close(fd);
	get_map_data(file, world, &tmp);
	check_closed_map(world, &tmp);
}

/* Check config specs other than map (textures and colors) */
static void	check_specs(int fd, t_world *world, t_tmp *tmp)
{
	tmp->line = get_next_line(fd, tmp);
	while (tmp->line)
	{
		if (ft_strcmp(tmp->line, "\n") && is_map_line(tmp->line, NULL))
			break ;
		if (ft_strcmp("\n", tmp->line))
			validate_lines(world, fd, tmp);
		free(tmp->line);
		tmp->line = get_next_line(fd, tmp);
	}
	if (all_textures_set_up(world))
	{
		validate_texture(world, fd, tmp);
		convert_to_int(world, tmp, fd, 'C');
		convert_to_int(world, tmp, fd, 'F');
	}
	else
		check_missing_identifier(world, fd, tmp);
}

/* Check color and texture identifiers */
static void	validate_lines(t_world *world, int fd, t_tmp *tmp)
{
	if (check_identifier(tmp->line, "NO"))
		world->tex_n = get_texture_inf(tmp, world, "NO", fd);
	else if (check_identifier(tmp->line, "SO"))
		world->tex_s = get_texture_inf(tmp, world, "SO", fd);
	else if (check_identifier(tmp->line, "WE"))
		world->tex_w = get_texture_inf(tmp, world, "WE", fd);
	else if (check_identifier(tmp->line, "EA"))
		world->tex_e = get_texture_inf(tmp, world, "EA", fd);
	else if (check_identifier(tmp->line, "F"))
		world->ground_str = get_texture_inf(tmp, world, "F", fd);
	else if (check_identifier(tmp->line, "C"))
		world->sky_str = get_texture_inf(tmp, world, "C", fd);
	else
	{
		if (all_textures_set_up(world))
			exit_on_error(world, fd, SPEC_UNEXPECTED, tmp);
		else
			exit_on_error(world, fd, SPEC_INVALID, tmp);
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
