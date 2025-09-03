/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:01:23 by malde-ch          #+#    #+#             */
/*   Updated: 2025/06/22 20:59:41 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float	distance_fish_eye(float cam_x, float halfF, t_dda *dda)
{
	float	dist;

	if (dda->side == 0)
		dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dist = dda->side_dist_y - dda->delta_dist_y;
	return (dist * cosf(atanf(cam_x * tanf(halfF))));
}

t_ray	compute_ray(int x, int w, float halfF, t_player *p)
{
	t_ray	ray;

	ray.cam_x = 2.0f * x / w - 1.0f;
	ray.dir = p->direction + atanf(ray.cam_x * tanf(halfF));
	return (ray);
}
