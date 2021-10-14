/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:22:03 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/14 18:55:07 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void	calculate(int *x, int *y, int z)
{	
	*x = (*x - *y) * cos(-0.8);
	*y = (*x + *y) * sin(-0.8) - z;
}

void	initialize_dates(t_values **maptrix, t_bresenham *dates)
{
	dates->increment = (1000/dates->columns) * -1;
	dates->z0 = maptrix[dates->x0][dates->y0].number * 2;
	dates->z1 = maptrix[dates->x1][dates->y1].number * 2;
	dates->x = dates->x0;
	dates->y = dates->y0;
	dates->x0 *= dates->increment;
	dates->y0 *= dates->increment;
	dates->x1 *= dates->increment;
	dates->y1 *= dates->increment;
	calculate(&dates->x0, &dates->y0, dates->z0);
	calculate(&dates->x1, &dates->y1, dates->z1);
	dates->dx = dates->x1 - dates->x0;
	dates->dy = dates->y1 - dates->y0;
}

void	swap(int *date1, int *date2)
{
	int	aux;

	aux = *date1;
	*date1 = *date2;
	*date2 = aux;
}

void	conditions(t_bresenham *things)
{
	if (things->dy >= 0)
		things->inc_y_i = 1;
	else
	{
		things->dy *= -1;
		things->inc_y_i = -1;
	}
	if (things->dx >= 0)
		things->inc_x_i = 1;
	else
	{
		things->dx *= -1;
		things->inc_x_i = -1;
	}
	if (things->dx >= things->dy)
	{
		things->inc_y_r = 0;
		things->inc_x_r = things->inc_x_i;
	}
	else
	{
		things->inc_x_r = 0;
		things->inc_y_r = things->inc_y_i;
		swap(&things->dy, &things->dx);
	}
}

void	to_write(t_values **maptrix, t_vars *mlx, t_bresenham *n)
{
	if (maptrix[n->x][n->y].color == 16777215)
	{
		if (n->z1 >= 20 || n->z0 >= 20)
		{
			if (n->z1 >= 20 && n->z0 >= 20)
				my_mlx_pixel_put(mlx, n->x0, n->y0, 15950335);
			else
				my_mlx_pixel_put(mlx, n->x0, n->y0, 15990528);
		}
		else
			my_mlx_pixel_put(mlx, n->x0, n->y0, 16777215);
	}
	else
		my_mlx_pixel_put(mlx, n->x0, n->y0, 16777215);
	(void)maptrix;
}

void	write_algorithm(t_values **maptrix, t_vars *mlx, t_bresenham *n)
{
	initialize_dates(maptrix, n);
	conditions(n);
	n->av_r = 2 * n->dy;
	n->av = n->av_r - n->dx;
	n->av_i = n->av - n->dx;
	n->x0 = n->x0 + 750;
	n->y0 = n->y0 + 500;
	while (n->x0 != n->x1 + 750 || n->y0 != n->y1 + 500)
	{
		to_write(maptrix, mlx, n);
		if (n->av >= 0)
		{
			n->x0 = n->x0 + n->inc_x_i;
			n->y0 = n->y0 + n->inc_y_i;
			n->av = n->av + n->av_i;
		}
		else
		{
			n->x0 = n->x0 + n->inc_x_r;
			n->y0 = n->y0 + n->inc_y_r;
			n->av = n->av + n->av_r;
		}
	}
}

void	write_map(t_values **maptrix, t_gdates num, t_vars mlx, t_bresenham *n)
{
	int	x;
	int	y;

	y = 0;
	while (y < num.columns)
	{
		x = 0;
		while (x < num.rows)
		{
			n->x0 = x;
			n->y0 = y;
			n->x1 = x + 1;
			n->y1 = y;
			if (x < num.rows - 1)
				write_algorithm(maptrix, &mlx, n);
			n->x0 = x;
			n->y0 = y;
			n->x1 = x;
			n->y1 = y + 1;
			if (y < num.columns - 1)
				write_algorithm(maptrix, &mlx, n);
			x += 1;
		}
		y += 1;
	}
}

void	start_draw(t_values **maptrix, t_gdates dates)
{
	t_vars		mlx;
	t_bresenham	n;

	ft_bzero(&n, sizeof(n));
	n.rows = dates.rows;
	n.columns = dates.columns;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1500, 1500, "fdf");
	mlx.img = mlx_new_image(mlx.mlx, 1500, 1500);
	mlx_hook(mlx.win, 17, 0, on_close, mlx.mlx);
	mlx_hook(mlx.win, 2, 0, esc_hook, mlx.mlx);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,
			&mlx.endian);
	write_map(maptrix, dates, mlx, &n);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	(void)dates;
}
