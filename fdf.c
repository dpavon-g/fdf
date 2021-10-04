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

void	write_algorithm(t_vars *mlx)
{
	int x0 = 0;
	int y0 = 0;
	int x1 = 200;
	int y1 = 0;

	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2; /* error value e_xy */

	for (;;){  /* loop */
	my_mlx_pixel_put(mlx, 500+x0, 500+y0, 0x00FFFFFF);
	if (x0 == x1 && y0 == y1) break;
	e2 = 2 * err;
	if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
	if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
}

	// int	x1 = 0;
	// int y1 = 0;
	// int	ynext = 100;
	// int	xnext = 10;
	// int	dY = ynext - y1;
	// int dX = xnext - x1;

	// int x = x1;
	// int y = y1;
	// int k;
	// int	IncYi;
	// int IncXi;
	// int	IncYr;
	// int IncXr;

	// if (dY >= 0)
	// 	IncYi = 1;
	// else
	// {
	// 	dY = -dY;
	// 	IncYi = -1;
	// }
	// if (dX >= 0)
	// 	IncXi = 1;
	// else
	// {
	// 	dX = -dX;
	// 	IncXi = -1;
	// }
	// if (dX >= dY)
	// {
	// 	IncYr = 0;
	// 	IncXr = IncXi;
	// }
	// else
	// {
	// 	IncXr = 0;
	// 	IncYr = IncYi;
	// 	k = dX;
	// 	dX = dY;
	// 	dY = k;
	// }

	// int av_r = 2*dY;
	// int av = av_r - dX;
	// int	av_i = av + dX;

	// while (x != xnext)
	// {
	// 	my_mlx_pixel_put(mlx, 500+x, 500+y, 0x00FFFFFF);
	// 	ft_printf("Valor de x: %d\nValor de y: %d\n", x, y);
	// 	if (av >= 0)
	// 	{
	// 		x = (x + IncXi);
	// 		y = (y + IncYi);
	// 		av = (av + av_i);    
	// 	}
	// 	else
	// 	{
	// 		x += IncXr;
	// 		y += IncYr;
	// 		av += av_r;
	// 	}
	// }
}

int main()
{
	t_vars 	mlx;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 1000, 1000, "Draw a pixel");
	mlx.img = mlx_new_image(mlx.mlx, 1000, 1000);

	mlx_hook(mlx.win, 17, 0, on_close, mlx.mlx);
	mlx_hook(mlx.win, 2, 0, esc_hook, mlx.mlx);

	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length, 
								&mlx.endian);
	write_algorithm(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}