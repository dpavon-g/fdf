/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:14 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 12:36:56 by dpavon-g         ###   ########.fr       */
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
int		get_color(char *str);
int		get_number(char letter1, char letter2);
int		know_dates(t_gdates *numbers);
int		number_columns(char **string);
void	start_draw(t_values **maptrix, t_gdates numbers);

#endif
