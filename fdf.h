/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:14 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/22 14:16:12 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"

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
#endif
