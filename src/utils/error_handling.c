/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/07/31 16:32:49 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	tex_and_color_err(t_err_code err);
static void	map_err(t_err_code err);
static void	find_error_msg(t_err_code err);

void	exit_file_analyze(t_world *world, int fd, t_err_code err)
{
	free_world(world);
	if (fd)
		close(fd);
	find_error_msg(err);
}

static void	find_error_msg(t_err_code err)
{
	if (err == INPUT_ARGC)
		printerr_exit("cub3D: invalid argument count\n"
			"Usage: ./cub3D map.cub\n");
	else if (err == CONFIG_OPEN)
		printerr_exit("Error\nFailed to open config file.\n");
	else if (err == MEMALLOC)
		printerr_exit("Error\nMemory allocation failed\n");
	else if (err == EXTRA_INFO)
		printerr_exit("Error\nUnexpected content after map\n");
	else if (err == UNEXPECTED_LINE)
		printerr_exit("Error\nUnexpected line after configuration\n");
	else if (err == INVAL_SPEC)
		printerr_exit("Error\nSpec misconfiguration\n");
	else if (err == DUPLICATE_IDENTIFIER)
		printerr_exit("Error\nDuplicate identifier\n");
	tex_and_color_err(err);
	map_err(err);
}

static void	tex_and_color_err(t_err_code err)
{
	if (err == INVAL_RGB)
		printerr_exit("Error\nInvalid RGB values\n");
	else if (err == INVAL_COLOR)
		printerr_exit("Error\nColor specs misconfiguration\n");
	else if (err == MISSING_COLOR)
		printerr_exit("Error\nColor identifiers missing\n");
	else if (err == XPM_FORMAT)
		printerr_exit("Error\nInvalid texture format: "
			"only XPM files accepted\n");
	else if (err == TEX_PATH)
		printerr_exit("Error\nTexture path misconfiguration\n");
	else if (err == MISSING_TEX)
		printerr_exit("Error\nTexture identifiers missing\n");
}

static void	map_err(t_err_code err)
{
	if (err == INVAL_PLAYER_POS)
		printerr_exit("Error\nInvalid player position\n");
	else if (err == MANY_PLAYER_POS)
		printerr_exit("Error\nMultiple player positions\n");
	else if (err == NO_PLAYER_POS)
		printerr_exit("Error\nMissing player position\n");
	else if (err == MAP_UNCLOSED)
		printerr_exit("Error\nMap not closed\n");
	else if (err == INVAL_MAP)
		printerr_exit("Error\nInvalid map\n");
}

void	printerr_exit(char *str)
{
	int		len;

	len = ft_strlen(str);
	write(STDERR_FILENO, str, len);
	exit(EXIT_FAILURE);
}
