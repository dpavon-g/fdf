/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:22:03 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:56:20 by dpavon-g         ###   ########.fr       */
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
