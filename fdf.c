/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/07 18:57:47 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	show_map(t_values **maptrix, t_gdates numbers)
{
	int i;
	int k;

	i = 0;
	//ft_printf("Columnas: %d\n", numbers.columns);
	//ft_printf("Filas: %d\n", numbers.rows);
	while (i < numbers.rows)
	{
		k = 0;
		while (k < numbers.columns)
		{
			ft_printf("%4d", maptrix[i][k].number);
			k++;
		}
		ft_printf("\n");
		i++;
	}
	(void)maptrix;
}

void leaks()
{
	system("leaks fdf");
}

int	main(void)
{
	int			flag;
	t_gdates	numbers;
	t_values	**maptrix;
	int			i;
	// Esto es lo que voy a usar para abrir la ventana gráfica.
	
	//atexit(leaks);
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
		ft_printf("Columnas: %d\n", numbers.columns);
		ft_printf("Filas: %d\n", numbers.rows);
		//ft_printf("Hola");
		//show_map(maptrix, numbers);
		start_draw(maptrix, numbers);
	}
	return (0);
}
