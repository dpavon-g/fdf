#include "fdf.h"

int	try(void *param)
{
	exit(0);
	(void)param;
	return (0);
}

int esc_hook(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	(void)param;
	return (0);
}

int main()
{

	t_vars		mlx_values;
	
	mlx_values.mlx = mlx_init();
	mlx_values.win = mlx_new_window(mlx_values.mlx, 1000, 1000, "fdf");

	mlx_hook(mlx_values.win, 17, 0, try, &mlx_values);
	mlx_hook(mlx_values.win, 2, 0, esc_hook, &mlx_values);
	mlx_loop(mlx_values.mlx);
}