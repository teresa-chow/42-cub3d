/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/02 11:35:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles TEXTURE configuration specifications */

#include "../../include/parse.h"
#include "../../include/utils.h"

static bool	check_texture_format(t_world *world, char *format);
static bool	check_texture_path(t_world *world);
static void	check_identifier_dup(t_tmp *tmp, t_world *world, char *id, int fd);

/* Get texture information */
char	*get_texture_inf(t_tmp *tmp, t_world *world, char *id, int fd)
{
	char	*s;
	char	*start;
	char	*end;
	int		i;

	check_identifier_dup(tmp, world, id, fd);
	i = 0;
	s = ft_strstr(tmp->line, id);
	identifier_value_exists(tmp, s + ft_strlen(id), world, fd);
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

static void	check_identifier_dup(t_tmp *tmp, t_world *world, char *id, int fd)
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
		exit_on_error(world, fd, SPEC_REPEATED, tmp);
}

/* Check each texture is valid */
void	validate_texture(t_world *world, int fd, t_tmp *tmp)
{
	if (!check_texture_format(world, ".xpm"))
		exit_on_error(world, fd, TEX_FORMAT, tmp);
	if (!check_texture_path(world))
		exit_on_error(world, fd, TEX_PATH, tmp);
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
	if (open(world->tex_n, __O_DIRECTORY) != -1
		|| open(world->tex_s, __O_DIRECTORY) != -1
		|| open(world->tex_e, __O_DIRECTORY) != -1
		|| open(world->tex_w, __O_DIRECTORY) != -1)
		return (0);
	if (open(world->tex_n, O_RDONLY) < 0
		|| open(world->tex_s, O_RDONLY) < 0
		|| open(world->tex_e, O_RDONLY) < 0
		|| open(world->tex_w, O_RDONLY) < 0)
		return (0);
	return (1);
}
