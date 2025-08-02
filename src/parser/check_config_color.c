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

static void	check_str_color(t_tmp *tmp, t_world *world, char id, int fd);
static int	check_only_digit(char *s, t_tmp *tmp, t_world *world, int fd);

/* Convert RGB color to decimal value */
void	convert_to_int(t_world *world, t_tmp *tmp, int fd, char id)
{
	char			**numbers;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	numbers = NULL;
	check_str_color(tmp, world, id, fd);
	if (id == 'C')
		numbers = ft_split(world->sky_str, ',');
	else
		numbers = ft_split(world->ground_str, ',');
	if (!numbers)
		exit_on_error(world, fd, MEMALLOC, tmp);
	r = ft_atoi(numbers[0]);
	g = ft_atoi(numbers[1]);
	b = ft_atoi(numbers[2]);
	if (r > 255 || g > 255 || b > 255)
		exit_on_error(world, fd, COLOR_RGB, tmp);
	free_numbers(numbers);
	if (id == 'C')
		world->sky = (r << 16 | g << 8 | b);
	else
		world->ground = (r << 16 | g << 8 | b);
}

static void	check_str_color(t_tmp *tmp, t_world *world, char id, int fd)
{
	int		i;
	char	*s;
	char	*s_tmp;

	i = 0;
	if (id == 'C')
		s = world->sky_str;
	else
		s = world->ground_str;
	s_tmp = s;
	while (*s_tmp)
	{
		if (*s_tmp == ',')
			i++;
		s_tmp++;
	}
	if (i != 2)
		exit_on_error(world, fd, COLOR_INVALID, tmp);
	if (check_only_digit(s, tmp, world, fd) < 0)
		exit_on_error(world, fd, COLOR_INVALID, tmp);
}

static int	check_only_digit(char *s, t_tmp *tmp, t_world *world, int fd)
{
	while (*s)
	{
		if (*s == '-')
			exit_on_error(world, fd, COLOR_RGB, tmp);
		if (!ft_isdigit(*s) && *s != ',')
			return (-1);
		s++;
	}
	return (0);
}
