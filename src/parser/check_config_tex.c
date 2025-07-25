/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/25 17:31:19 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles TEXTURE configuration specifications */

#include "../../include/parse.h"

void    validate_texture_path_and_format(t_world *world, int fd)
{
        if (open(world->tex_n, O_RDONLY) < 0 || open(world->tex_s, O_RDONLY) < 0 
                || open(world->tex_e, O_RDONLY) < 0 || open(world->tex_w, O_RDONLY) < 0)
		exit_file_analyze(world, fd, "Error\nTexture path failure\n");
        else
        {
		if (!ft_strstr(world->tex_n, ".xpm") || !ft_strstr(world->tex_s, ".xpm") 
		|| !ft_strstr(world->tex_e, ".xpm") || !ft_strstr(world->tex_w, ".xpm"))
			exit_file_analyze(world, fd, "Error\nInvalid texture format. "
				"The correct format is .xpm!\n");
        }
}

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