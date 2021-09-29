/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/29 10:55:06 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_the_map(void)
{
	int			flag;
	t_gdates	numbers;
	t_values	**maptrix;
	int			i;
	// Esto es lo que voy a usar para abrir la ventana gráfica.
	i = 0;
	ft_bzero(&numbers, sizeof(numbers));
	numbers.map = "maps/10-2.fdf";
	flag = know_dates(&numbers);
	if (flag == 0)
	{
		ft_printf("Map loaded!!\n");
		maptrix = malloc(sizeof(maptrix) * numbers.rows);
		while (i < numbers.rows)
		{
			maptrix[i] = malloc(sizeof(maptrix) * numbers.columns);
			i++;
		}
		flag = charge_map(maptrix, numbers);
	}
	if (flag == 1)
		ft_printf("Error!\n");
	else
	{
		/*
			Aquí tendría que ir la función encargada de realizar todo lo gráfico con la minilib
		*/
	}
	//Tienes leak porque tienes que liberar la matriz de los datos creados anteriormente.
	return (0);
}
