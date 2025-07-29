/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/27 23:01:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles TEXTURE configuration specifications */

#include "../../include/parse.h"

static bool	check_texture_format(t_world *world, char *format);
static bool	check_texture_path(t_world *world);
static void	check_identifier_dup(char *id, t_world *world, int fd);

/* Get texture information */
char	*get_texture_inf(char *line, char *id, t_world *world, int fd)
{
	char	*s;
	char	*start;
	char	*end;
	int	i;

	check_identifier_dup(id, world, fd);
	i = 0;
	s = ft_strstr(line, id);
	find_identifier_value(s + ft_strlen(id), world, fd, id);
	s += 2;
	start = NULL;
	end = NULL;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] && !ft_isspace(s[i]))
		start = &s[i];
	end = &start[ft_strlen(start) - 1];
	while (*end == '\n' || ft_isspace(*end))
		end--;
	return (ft_substr(start, 0, (end - start) + 1));
}

static void	check_identifier_dup(char *id, t_world *world, int fd)
{
	bool	dup;

	dup = false;
	if (!ft_strcmp(id, "NO") && world->tex_n)
		dup = true;
	else if (!ft_strcmp(id, "SO") && world->tex_s)
		dup = true;
	else if (!ft_strcmp(id, "WE") && world->tex_w)
		dup = true;
	else if (!ft_strcmp(id, "EA") && world->tex_e)
		dup = true;
	else if (!ft_strcmp(id, "F") && world->ground_str)
		dup = true;
	else if (!ft_strcmp(id, "C") && world->sky_str)
		dup = true;
	if (dup)
		exit_file_analyze(world, fd, "Error\nDuplicate identifier is not allowed!\n", NULL);
}

/* Check each texture is valid */
void    validate_texture(t_world *world, int fd)
{
	if (!check_texture_format(world, ".xpm"))
		exit_file_analyze(world, fd, "Error\nInvalid texture format. "
			"Only .xpm files are accepted\n", NULL);
	if (!check_texture_path(world))
		exit_file_analyze(world, fd, "Error\nTexture path misconfiguration\n", NULL);
}

static bool	check_texture_format(t_world *world, char *format)
{
	if (!check_file_format(world->tex_n, format)
		|| !check_file_format(world->tex_s, format) 
		|| !check_file_format(world->tex_e, format)
		|| !check_file_format(world->tex_w, format))
		return (0);
	return (1);
}

static bool	check_texture_path(t_world *world)
{
		if (open(world->tex_n, O_RDONLY) < 0
			|| open(world->tex_s, O_RDONLY) < 0 
			|| open(world->tex_e, O_RDONLY) < 0
			|| open(world->tex_w, O_RDONLY) < 0)
		return (0);
	return (1);
}
