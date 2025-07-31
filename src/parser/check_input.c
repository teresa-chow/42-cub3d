/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:17:18 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/31 18:43:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles command line argument errors */

#include "../../include/parse.h"
#include "../../include/utils.h"

static bool	check_file_name(char *str);

bool	check_input(int argc, char *map)
{
	if (argc != 2)
	{
		printerr_exit("cub3D: invalid argument count\n"
			"Usage: ./cub3D map.cub\n", NULL);
		return (0);
	}
	if (!check_file_name(map))
	{
		printerr_exit("cub3D: invalid file type\n"
			"Usage: ./cub3D map.cub\n", NULL);
		return (0);
	}
	return (1);
}

static bool	check_file_name(char *str)
{
	if (!str)
		return (0);
	if (ft_strlen(str) < 4)
		return (0);
	if (!check_file_format(str, ".cub"))
		return (0);
	return (1);
}
