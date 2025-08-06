/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:20:52 by tchow-so          #+#    #+#             */
/*   Updated: 2025/08/06 10:59:46 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

static void	err_input(t_err_code err, int fd);
static void	err_config(t_err_code err, int fd);
static void	err_map_content(t_err_code err, int fd);
static void	err_mlx(t_err_code err, int fd);

void	print_error(t_err_code err)
{
	if (err == MEMALLOC)
		ft_putstr_fd("Error\nMemory allocation failed\n", STDERR_FILENO);
	err_input(err, STDERR_FILENO);
	err_config(err, STDERR_FILENO);
	err_map_content(err, STDERR_FILENO);
	err_mlx(err, STDERR_FILENO);
	return ;
}

/* print_error helper functions */
static void	err_input(t_err_code err, int fd)
{
	if (err == INPUT_ARGC)
		ft_putstr_fd("cub3D: invalid argument count\n"
			"Usage: ./cub3D map.cub\n", fd);
	else if (err == INPUT_FORMAT)
		ft_putstr_fd("cub3D: invalid file type\n"
			"Usage: ./cub3D map.cub\n", fd);
}

static void	err_config(t_err_code err, int fd)
{
	if (err == CONFIG_OPEN)
		ft_putstr_fd("Error\nFailed to open config file\n", fd);
	else if (err == SPEC_UNEXPECTED)
		ft_putstr_fd("Error\nUnexpected line after configuration\n", fd);
	else if (err == SPEC_INVALID)
		ft_putstr_fd("Error\nSpec misconfiguration\n", fd);
	else if (err == SPEC_REPEATED)
		ft_putstr_fd("Error\nRepeated identifier\n", fd);
	if (err == COLOR_RGB)
		ft_putstr_fd("Error\nInvalid RGB values\n", fd);
	else if (err == COLOR_INVALID)
		ft_putstr_fd("Error\nColor specs misconfiguration\n", fd);
	else if (err == COLOR_MISSING)
		ft_putstr_fd("Error\nColor identifiers missing\n", fd);
	else if (err == TEX_FORMAT)
		ft_putstr_fd("Error\nInvalid texture format: "
			"only XPM files accepted\n", fd);
	else if (err == TEX_PATH)
		ft_putstr_fd("Error\nTexture path misconfiguration\n", fd);
	else if (err == TEX_MISSING)
		ft_putstr_fd("Error\nTexture identifiers missing\n", fd);
	else if (err == MAP_EXTRA)
		ft_putstr_fd("Error\nUnexpected content after map\n", fd);
}

static void	err_map_content(t_err_code err, int fd)
{
	if (err == PLAYER_POS_INVALID)
		ft_putstr_fd("Error\nInvalid player position\n", fd);
	else if (err == PLAYER_POS_EXTRA)
		ft_putstr_fd("Error\nMultiple player positions\n", fd);
	else if (err == PLAYER_POS_NONE)
		ft_putstr_fd("Error\nMissing player position\n", fd);
	else if (err == MAP_OPEN)
		ft_putstr_fd("Error\nMap not closed\n", fd);
	else if (err == MAP_INVALID)
		ft_putstr_fd("Error\nMap content misconfiguration\n", fd);
	else if (err == MAP_SIZE)
		ft_putstr_fd("Error\nMap size too big "
			"- maximum accepted map area: 91200\n", fd);
	else if (err == MINIMAP_SIZE)
		ft_putstr_fd("Error\nMap size too big to print minimap "
			"- use regular version instead\n", fd);
}

static void	err_mlx(t_err_code err, int fd)
{
	if (err == MLX_INIT)
		ft_putstr_fd("MiniLibX: Failed to initialize MLX\n", fd);
	else if (err == MLX_WIN)
		ft_putstr_fd("MiniLibX: Failed to open window\n", fd);
	else if (err == MLX_IMG)
		ft_putstr_fd("MiniLibX: Failed to create new image\n", fd);
}
