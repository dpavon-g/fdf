#include "fdf.h"

int esc_hook(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	(void)param;
	return (0);
}

int	on_close(void *param)
{
	exit(0);
	(void)param;
	return (0);
}

void	my_mlx_pixel_put(t_vars *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	calculate(int *x, int *y, int z)
{	
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	write_algorithm(t_vars *mlx, int x0, int y0, int x1, int y1, t_values **maptrix)
{
	/*
		Zeta es el valor d
	*/
	int	z = maptrix[x0][y0].number;
	int z1 = maptrix[x1][y1].number;
	int increment;
	increment = 30;
	x0 *= increment;
	y0 *= increment;
	x1 *= increment;
	y1 *= increment;
	calculate(&x0, &y0, z);
	calculate(&x1, &y1, z1);
	(void)maptrix;
	int dx = x1 - x0;
	int	dy = y1 - y0;
	int incYi;
	int	incXi;
	int incXr;
	int	incYr;
	int	aux;
	if (dy >= 0)
		incYi = 1;
	else
	{
		dy *= -1;
		incYi = -1;
	}
	if (dx >= 0)
		incXi = 1;
	else
	{
		dx *= -1;
		incXi = -1;
	}
	if (dx >= dy)
	{
		incYr = 0;
		incXr = incXi;
	}
	else
	{
		incXr = 0;
		incYr = incYi;
		aux = dx;
		dx = dy;
		dy = aux;
	}
	int	avR = 2 * dy;
	int av = avR - dx;
	int avI = av - dx;
	
	x0 = x0 + 500;
	y0 = y0 + 250;

	while (x0 != x1 + 500 || y0 != y1 + 250)
	{
		if ((x0 >= 0 && x0 <= 1500) && (y0 >= 0 && y0 <= 1500))
			my_mlx_pixel_put(mlx, x0, y0, 0x00FFFFFF);
		if (av >= 0)
		{
			x0 = x0 + incXi;
			y0 = y0 + incYi;
			av = av + avI;
		}
		else
		{
			x0 = x0 + incXr;
			y0 = y0 + incYr;
			av = av + avR;
		}
	}
}

void	write_map(t_values **maptrix, t_gdates	numbers, t_vars mlx)
{
	int y;
	int	x;
	int inc;

	inc = 50;
	y = 0;
	while (y < numbers.columns)
	{
		x = 0;
		while (x < numbers.rows)
		{
			if (x < numbers.rows-1)
				write_algorithm(&mlx, x, y, (x+1), (y), maptrix);
			if (y < numbers.columns-1)
				write_algorithm(&mlx, x, y, (x), (y+1), maptrix);
			//my_mlx_pixel_put(&mlx, 100*x, 100*y, 0x00FFFFFF);
			x++;
		}
		y++;
	}
	(void)maptrix;
	(void)mlx;
}

void	start_draw(t_values **maptrix, t_gdates	numbers)
{
	t_vars 	mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1500, 1500, "Draw a pixel");
	mlx.img = mlx_new_image(mlx.mlx, 1500, 1500);

	mlx_hook(mlx.win, 17, 0, on_close, mlx.mlx);
	mlx_hook(mlx.win, 2, 0, esc_hook, mlx.mlx);

	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, 
								&mlx.endian);
	write_map(maptrix, numbers, mlx);
	//write_algorithm(&mlx, 0, 0, 100, 0, maptrix);
	// write_algorithm(&mlx, 0, 0, 0, 100, maptrix);
	// write_algorithm(&mlx, 100, 0, 100, 100, maptrix);
	// write_algorithm(&mlx, 100, 100, 0, 100, maptrix);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
	(void)numbers;
}