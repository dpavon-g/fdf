/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:22:03 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/20 19:18:18 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && x < 1500 && y > 0 && y < 1500)
	{
		dst = data->addr + (y * data->line_length
				+ x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	on_close(void *param)
{
	exit(0);
	(void)param;
	return (0);
}

int	esc_hook(int key, void *param)
{
	if (key == 53)
		exit(0);
	(void)param;
	return (0);
}

void	c_z(int *x, int *y, int z)
{	
	*x = (*x - *y) * cos(0.8);
	*y = ((*x + *y) * sin(0.8) - z * 1.5);
}

int	calculate_color(int orig, int dest, int dist)
{
	int	dif;

	dif = orig - dest;
	dif /= dist;
	return (dif);
}

void	write_line(t_vector orig, t_vector dest, t_vars mlx, t_values **map)
{
	float	dist;
	float	step_x;
	float	step_y;
	float	i;
	int		dif;

	orig.color = map[orig.y][orig.x].color;
	dest.color = map[dest.y][dest.x].color;
	orig.x *= mlx.incre;
	orig.y *= mlx.incre;
	dest.x *= mlx.incre;
	dest.y *= mlx.incre;
	c_z(&orig.x, &orig.y, map[orig.y / mlx.incre][orig.x / mlx.incre].number);
	c_z(&dest.x, &dest.y, map[dest.y / mlx.incre][dest.x / mlx.incre].number);
	dist = sqrt(pow(orig.x - dest.x, 2) + pow(orig.y - dest.y, 2));
	dif = calculate_color(orig.color, dest.color, dist);
	step_x = (dest.x - orig.x) / dist;
	step_y = (dest.y - orig.y) / dist;
	i = -1;
	while (++i < dist)
	{
		my_mlx_pixel_put(&mlx, (orig.x + step_x * i)
			+ 750, (orig.y + step_y * i) + 500, orig.color - (dif * i));
	}
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

void	start_draw(t_values **maptrix, t_gdates dates)
{
	t_structs	n;

	ft_bzero(&n, sizeof(n));
	n.maptrix = maptrix;
	n.dates = dates;
	n.mlx.mlx = mlx_init();
	n.mlx.win = mlx_new_window(n.mlx.mlx, 1500, 1500, "fdf");
	n.mlx.img = mlx_new_image(n.mlx.mlx, 1500, 1500);
	n.mlx.incre = ((1000 / dates.columns));
	mlx_hook(n.mlx.win, 17, 0, on_close, n.mlx.mlx);
	mlx_hook(n.mlx.win, 2, 0, esc_hook, n.mlx.mlx);
	n.mlx.addr = mlx_get_data_addr(n.mlx.img, &n.mlx.bits_per_pixel,
			&n.mlx.line_length, &n.mlx.endian);
	write_map(n.maptrix, n.dates, n.mlx);
	mlx_put_image_to_window(n.mlx.mlx, n.mlx.win, n.mlx.img, 0, 0);
	mlx_loop(n.mlx.mlx);
	(void)dates;
}
