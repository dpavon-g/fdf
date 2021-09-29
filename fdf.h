/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:14 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/29 10:16:30 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

typedef struct s_dates
{
	int	color;
	int	number;
}	t_values;

typedef struct s_generics
{
	int		rows;
	int		columns;
	char	*map;
}	t_gdates;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;


int	charge_map(t_values **maptrix, t_gdates numbers);
int	get_color(char *str);
int	get_number(char letter1, char letter2);
int	know_dates(t_gdates *numbers);
int	number_columns(char **string);

#endif
