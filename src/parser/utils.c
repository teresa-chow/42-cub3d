/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 15:42:55 by carlaugu          #+#    #+#             */
/*   Updated: 2025/07/31 17:25:30 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"
#include "../../include/utils.h"

bool	check_file_format(char *str, char *format)
{
	int			i;
	int			j;

	i = ft_strlen(str) - 4;
	j = 0;
	while (j < 4)
	{
		if (str[i++] != format[j++])
			return (0);
	}
	return (1);
}

char	**map_dup(t_world *world)
{
	char	**map_copy;
	int	i;

	map_copy = ft_calloc(world->map_len + 1, sizeof(char *));
	if (!map_copy)
		exit_file_analyze(world, 0, "Error\nMemory allocation failed\n", NULL);
	i = -1;
	while (++i < world->map_len)
	{
		map_copy[i] = ft_substr(world->map[i], 0,
				ft_strlen(world->map[i]));
		if (!map_copy[i])
			exit_file_analyze(world, 0, "Error\n"
				"Memory allocation failed\n", NULL);
	}
	return(map_copy);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

size_t	strlen_newline(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}
