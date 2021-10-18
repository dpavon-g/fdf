/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:22:03 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/15 19:18:54 by dpavon-g         ###   ########.fr       */
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

void	calculate(int *x, int *y, int z, t_bresenham *n)
{	
	*x = (*x - *y) * cos(n->cos);
	*y = ((*x + *y) * sin(n->sen) - z);
	(void)n;
}

void	initialize_dates(t_values **maptrix, t_bresenham *dates)
{
	dates->z0 = (maptrix[dates->x0][dates->y0].number * 2);
	dates->z1 = (maptrix[dates->x1][dates->y1].number * 2);
	dates->x = dates->x0;
	dates->y = dates->y0;
	dates->x0 *= dates->increment;
	dates->y0 *= dates->increment;
	dates->x1 *= dates->increment;
	dates->y1 *= dates->increment;
	calculate(&dates->x0, &dates->y0, dates->z0, dates);
	calculate(&dates->x1, &dates->y1, dates->z1, dates);
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
	
	if (n->z1 >= 20 || n->z0 >= 20)
		{
			if (n->z0 >= 20 && n->z1 >= 20)
				maptrix[n->x][n->y].color = 15950335;
			else
			{
				maptrix[n->x][n->y].color = 16777215;
			}
		}
	else
		maptrix[n->x][n->y].color = 16777215;	
	if (n->x0 >= 0 && n->x0 < 1500 && n->y0 >= 0 && n->y0 < 1500)
		my_mlx_pixel_put(mlx, n->x0, n->y0, maptrix[n->x][n->y].color);
	n->position_line++;
	(void)maptrix;

}

void	write_algorithm(t_values **maptrix, t_vars *mlx, t_bresenham *n)
{
	initialize_dates(maptrix, n);
	conditions(n);
	n->av_r = 2 * n->dy;
	n->av = n->av_r - n->dx;
	n->av_i = n->av - n->dx;
	n->x0 = n->x0 + n->position_x;
	n->y0 = n->y0 + n->position_y;
	n->position_line = 0;
	while (n->x0 != n->x1 + n->position_x || n->y0 != n->y1 + n->position_y)
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
		n->position += 1;
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
			n->position = 0;
			n->x0 = x;
			n->y0 = y;
			n->x1 = x + 1;
			n->y1 = y;
			if (x < num.rows - 1)
				write_algorithm(maptrix, &mlx, n);
			n->x0 = x;
			n->y0 = y;
			n->x1 = x++;
			n->y1 = y + 1;
			if (y < num.columns - 1)
				write_algorithm(maptrix, &mlx, n);
		}
		y += 1;
	}
}

void	move_conditions(int key, t_bresenham *n)
{
	if (key == 7)
	{
		if (n->increment < ((1000 / n->columns) * -1))
			n->increment += 10;
	}
	else if (key == 1)
		n->position_y += 10;
	else if (key == 13)
		n->position_y -= 10;
	else if (key == 2)
		n->position_x += 10;
	else if (key == 0)
		n->position_x -= 10;
	else if (key == 123)
	{
		n->cos -= -0.1;
	}
	else if (key == 124)
	{
		n->cos += -0.1;
	}
}

int	move_screen(int key, t_bresenham *n)
{
	ft_printf("Tecla: %d\n", key);
	if (key == 126 || key == 125 || key == 6 || key == 7 || key == 13
			|| key == 1 || key == 0 || key == 2 || key == 123 || key == 124)
	{
		if (key == 126)
			n->sen += 0.1;
		else if (key == 125)
			n->sen -= 0.1;
		else if (key == 6)
		{
			n->increment -= 10;
		}
		move_conditions(key, n);
		mlx_clear_window(n->mlx.mlx, n->mlx.win);
		n->mlx.img = mlx_new_image(n->mlx.mlx, 1500, 1500);
		n->mlx.addr = mlx_get_data_addr(n->mlx.img, &n->mlx.bits_per_pixel,
				&n->mlx.line_length, &n->mlx.endian);
		write_map(n->maptrix, n->dates, n->mlx, n);
		mlx_put_image_to_window(n->mlx.mlx, n->mlx.win, n->mlx.img, 0, 0);
		mlx_loop(n->mlx.mlx);
	}
	return (0);
}

int	zoom(int key, t_bresenham *n)
{
	ft_printf("Tecla: %d", key);
	if (key == 6 || key == 7)
	{
		mlx_clear_window(n->mlx.mlx, n->mlx.win);
		n->mlx.img = mlx_new_image(n->mlx.mlx, 1500, 1500);
		n->mlx.addr = mlx_get_data_addr(n->mlx.img, &n->mlx.bits_per_pixel,
				&n->mlx.line_length, &n->mlx.endian);
		write_map(n->maptrix, n->dates, n->mlx, n);
		mlx_put_image_to_window(n->mlx.mlx, n->mlx.win, n->mlx.img, 0, 0);
		mlx_loop(n->mlx.mlx);
	}
	(void)n;
	return (0);
}

void	start_draw(t_values **maptrix, t_gdates dates)
{
	t_bresenham	n;

	ft_bzero(&n, sizeof(n));
	n.maptrix = maptrix;
	n.dates = dates;
	n.sen = -0.8;
	n.cos = -0.8;
	n.rows = dates.rows;
	n.columns = dates.columns;
	n.position_x = 750;
	n.position_y = 500;
	n.increment = ((1000 / n.columns) * -1);
	n.mlx.mlx = mlx_init();
	n.mlx.win = mlx_new_window(n.mlx.mlx, 1500, 1500, "fdf");
	n.mlx.img = mlx_new_image(n.mlx.mlx, 1500, 1500);
	mlx_hook(n.mlx.win, 17, 0, on_close, n.mlx.mlx);
	mlx_hook(n.mlx.win, 2, 0, esc_hook, n.mlx.mlx);
	mlx_key_hook(n.mlx.win, move_screen, &n);
	n.mlx.addr = mlx_get_data_addr(n.mlx.img, &n.mlx.bits_per_pixel,
			&n.mlx.line_length, &n.mlx.endian);
	write_map(n.maptrix, n.dates, n.mlx, &n);
	mlx_put_image_to_window(n.mlx.mlx, n.mlx.win, n.mlx.img, 0, 0);
	mlx_loop(n.mlx.mlx);
	(void)dates;
}
