/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:56:48 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:56:55 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	keys_option(int key, t_structs *n)
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
}

int	move_screen(int key, t_structs *n)
{
	if (key == 6 || key == 7 || key == 123 || key == 124
		|| key == 126 || key == 125 || key == 8 || key == 9
		|| key == 3 || key == 5)
	{
		keys_option(key, n);
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
