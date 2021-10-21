/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:22:03 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 16:02:50 by dpavon-g         ###   ########.fr       */
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

void	calculate_z(int *x, int *y, int z, t_vars mlx)
{	
	*x = (*x - *y) * cos(mlx.cos);
	*y = ((*x + *y) * sin(mlx.sen) - z * mlx.height);
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
	{
		my_mlx_pixel_put(&mlx, (orig.x + step_x * i)
			+ mlx.position.x, (orig.y + step_y * i)
			+ mlx.position.y, orig.color - (dif * i));
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

int	move_screen(int key, t_structs *n)
{
	ft_printf("Tecla: %d\n", key);
	if (key == 6 || key == 7 || key == 123 || key == 124 
			|| key == 126 || key == 125 || key == 8 || key == 9
			|| key == 3 || key == 5)
	{
		if (key == 6)
			n->mlx.incre += 10;
		if (key == 7)
		{
			if (n->mlx.incre > 10)
				n->mlx.incre -= 10;
		}
		if (key == 124)
			n->mlx.position.x += 10;
		if (key == 123)
			n->mlx.position.x -= 10;
		if (key == 125)
			n->mlx.position.y += 10;
		if (key == 126)
			n->mlx.position.y -= 10;
		if (key == 8)
			n->mlx.sen += 0.1;
		if (key == 9)
			n->mlx.sen -= 0.1;
		if (key == 3)
			n->mlx.height += 0.5;
		if (key == 5)
			n->mlx.height -= 0.5;
		mlx_clear_window(n->mlx.mlx, n->mlx.win);
		n->mlx.img = mlx_new_image(n->mlx.mlx, 1500, 1500);
		n->mlx.addr = mlx_get_data_addr(n->mlx.img, &n->mlx.bits_per_pixel,
				&n->mlx.line_length, &n->mlx.endian);
		write_map(n->maptrix, n->dates, n->mlx);
		mlx_put_image_to_window(n->mlx.mlx, n->mlx.win, n->mlx.img, 0, 0);
		mlx_loop(n->mlx.mlx);
	}
	return (0);
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
	n.mlx.cos = 0.8;
	n.mlx.sen = 0.8;
	n.mlx.height = 1.5;
	n.mlx.position.x = 800;
	n.mlx.position.y = 250;
	n.mlx.incre = ((1000 / dates.columns));
	mlx_hook(n.mlx.win, 17, 0, on_close, n.mlx.mlx);
	mlx_hook(n.mlx.win, 2, 0, esc_hook, n.mlx.mlx);
	mlx_key_hook(n.mlx.win, move_screen, &n);
	n.mlx.addr = mlx_get_data_addr(n.mlx.img, &n.mlx.bits_per_pixel,
			&n.mlx.line_length, &n.mlx.endian);
	write_map(n.maptrix, n.dates, n.mlx);
	mlx_put_image_to_window(n.mlx.mlx, n.mlx.win, n.mlx.img, 0, 0);
	mlx_loop(n.mlx.mlx);
	(void)dates;
}
