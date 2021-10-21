/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:57:28 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:57:29 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calculate_z(int *x, int *y, int z, t_vars mlx)
{	
	*x = (*x - *y) * cos(mlx.cos);
	*y = ((*x + *y) * sin(mlx.sen) - z * mlx.height);
}

int	calculate_color(int orig, int dest, int dist)
{
	int	dif;

	dif = dest - orig;
	dif /= dist;
	return (dif);
}

void	init_values(t_values **map, t_vector *orig, t_vector *dest, t_vars mlx)
{
	orig->color = map[orig->y][orig->x].color;
	dest->color = map[dest->y][dest->x].color;
	orig->x *= mlx.incre;
	orig->y *= mlx.incre;
	dest->x *= mlx.incre;
	dest->y *= mlx.incre;
}

void	write_line(t_vector orig, t_vector dest, t_vars mlx, t_values **map)
{
	float	dist;
	float	step_x;
	float	step_y;
	float	i;
	int		dif;

	init_values(map, &orig, &dest, mlx);
	calculate_z(&orig.x, &orig.y,
		map[orig.y / mlx.incre][orig.x / mlx.incre].number, mlx);
	calculate_z(&dest.x,
		&dest.y, map[dest.y / mlx.incre][dest.x / mlx.incre].number, mlx);
	dist = sqrt(pow(orig.x - dest.x, 2) + pow(orig.y - dest.y, 2));
	dif = calculate_color(orig.color, dest.color, dist);
	step_x = (dest.x - orig.x) / dist;
	step_y = (dest.y - orig.y) / dist;
	i = -1;
	while (++i < dist)
		my_mlx_pixel_put(&mlx, (orig.x + step_x * i)
			+ mlx.position.x, (orig.y + step_y * i)
			+ mlx.position.y, orig.color + (dif * i));
	(void)map;
}

void	write_map(t_values **maptrix, t_gdates num, t_vars mlx)
{
	t_vector	from;
	t_vector	to;

	from.y = 0;
	while (from.y < num.rows)
	{
		from.x = 0;
		while (from.x < num.columns)
		{
			to.x = from.x + 1;
			to.y = from.y;
			if (from.x < num.columns - 1)
				write_line(to, from, mlx, maptrix);
			to.x = from.x;
			to.y = from.y + 1;
			if (from.y < num.rows - 1)
				write_line(to, from, mlx, maptrix);
			from.x++;
		}
		from.y++;
	}
	(void)maptrix;
	(void)mlx;
}
