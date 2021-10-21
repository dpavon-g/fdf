/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:14 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:51:21 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_dates
{
	int	color;
	int	number;
}	t_values;

typedef struct s_generics
{
	int		rows;
	int		columns;
	int		flag;
	char	*map;
}	t_gdates;

typedef struct s_vector
{
	int	x;
	int	y;
	int	color;
}	t_vector;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	void		*pointer;
	char		*pixels;
	t_vector	size;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			incre;
	t_vector	position;
	float		cos;
	float		sen;
	float		height;
}	t_vars;

typedef struct s_structs
{
	t_vars		mlx;
	t_values	**maptrix;
	t_gdates	dates;
}	t_structs;

int		charge_map(t_values **maptrix, t_gdates dates);
void	rgb_to_decimal(int *r, int *b, int *g, char *string);
int		is_digit(char *str);
int		good_value(char *str);
int		get_color(char *str);
int		get_number(char letter1, char letter2);
int		know_dates(t_gdates *numbers);
int		number_columns(char **string);
void	start_draw(t_values **maptrix, t_gdates numbers);
void	my_mlx_pixel_put(t_vars *data, int x, int y, int color);
int		on_close(void *param);
int		esc_hook(int key, void *param);
void	calculate_z(int *x, int *y, int z, t_vars mlx);
int		calculate_color(int orig, int dest, int dist);
void	init_values(t_values **map, t_vector *orig, t_vector *dest, t_vars mlx);
void	write_line(t_vector orig, t_vector dest, t_vars mlx, t_values **map);
void	write_map(t_values **maptrix, t_gdates num, t_vars mlx);
int		move_screen(int key, t_structs *n);
void	keys_option(int key, t_structs *n);
void	start_draw(t_values **maptrix, t_gdates dates);
void	save_map(t_vector	coord, t_values **maptrix, t_gdates dates, int fd);

#endif
