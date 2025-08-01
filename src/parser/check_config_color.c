/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 13:31:40 by carlaugu          #+#    #+#             */
/*   Updated: 2025/08/01 16:14:57 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This file handles COLOR configuration specifications */

#include "../../include/parse.h"
#include "../../include/utils.h"

static void	check_str_color(char id, t_world *world, int fd);
static int	check_only_digit(char *s);

/* Convert RGB color to decimal value */
void	convert_to_int(t_world *world, int fd, char id)
{
	char			**numbers;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	numbers = NULL;
	check_str_color(id, world, fd);
	if (id == 'C')
		numbers = ft_split(world->sky_str, ',');
	else
		numbers = ft_split(world->ground_str, ',');
	if (!numbers)
		exit_on_error(world, fd, MEMALLOC);
	r = ft_atoi(numbers[0]);
	g = ft_atoi(numbers[1]);
	b = ft_atoi(numbers[2]);
	if (r > 255 || g > 255 || b > 255)
		exit_on_error(world, fd, COLOR_RGB);
	free_numbers(numbers);
	if (id == 'C')
		world->sky = (r << 16 | g << 8 | b);
	else
		world->ground = (r << 16 | g << 8 | b);
}

static void	check_str_color(char id, t_world *world, int fd)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	if (id == 'C')
		s = world->sky_str;
	else
		s = world->ground_str;
	tmp = s;
	while (*tmp)
	{
		if (*tmp == ',')
			i++;
		tmp++;
	}
	if (i != 2)
		exit_on_error(world, fd, COLOR_INVALID);
	if (check_only_digit(s) < 0)
		exit_on_error(world, fd, COLOR_INVALID);
}

static int	check_only_digit(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != ',')
			return (-1);
		s++;
	}
	return (0);
}
