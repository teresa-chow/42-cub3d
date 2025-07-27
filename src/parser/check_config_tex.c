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

/* Get texture information */
char	*get_texture_inf(char *line, char *id)
{
	char	*s;
	char	*start;
	char	*end;
	int	i;

	i = 0;
	s = ft_strstr(line, id);
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

/* Check each texture is valid */
void    validate_texture(t_world *world, int fd)
{
	if (!check_texture_format(world, ".xpm"))
		exit_file_analyze(world, fd, "Error\nInvalid texture format. "
			"Only .xpm files are accepted\n");
	if (!check_texture_path(world))
		exit_file_analyze(world, fd, "Error\nTexture path misconfiguration.\n");
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
