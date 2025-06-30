/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so <tchow-so@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 14:31:02 by tchow-so          #+#    #+#             */
/*   Updated: 2025/06/30 16:52:50 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int raycaster(int argc, char **argv)
{
    // x and y start position
    double  pos_x = 22;
    double  pos_y = 12;
    // initial direction vector (direction player is facing)
    double  dir_x = -1;
    double  dir_y = 0;
    // camera plane
    double  plane_x = 0;
    double  plane_y = 0.66;

    //time of current and previous frames
    double  time_curr = 0;
    double  time_prev = 0;

    //init_mlx
    while (1) // while(active)
    {
        int x = 0;
        while (x < w)
        {
            double camera_x = 2 * x / (double)w - 1; //x-coordinate in camera space (?)
            x++;
        }
    }
}

/*
- camera plane vector
- direction vector
- field of vision (fov)
if the camera plane vector and the direction vector are the same legth:
    fov 90 degrees

- fps count

- rotation matrix:
[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]
*/