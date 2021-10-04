/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/04 13:44:03 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_map(t_values **maptrix, t_gdates numbers)
{
	int i;
	int k;

	i = 0;
	while (i < numbers.columns)
	{
		k = 0;
		while (k < numbers.rows)
		{
			ft_printf("%4d", maptrix[i][k].number);
			k++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(void)
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
		show_map(maptrix, numbers);
		
	}

	//Tienes leak porque tienes que liberar la matriz de los datos creados anteriormente.
	return (0);
}
