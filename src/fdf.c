/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 11:42:08 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/18 16:05:00 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	select_map(t_gdates *dates)
{
	char	*string;
	char	*aux;

	get_next_line(0, &string);
	aux = string;
	string = ft_strjoin(string, ".fdf");
	free(aux);
	dates->map = ft_strjoin("maps/", string);
	free(string);
}

void	liberate_map(t_values ***maptrix, t_gdates *dates)
{
	int	i;

	i = 0;
	while (i < dates->rows)
	{
		free((*maptrix)[i]);
		i++;
	}
	free(*maptrix);
	free(dates->map);
}

int	main(void)
{
	int			i;
	t_gdates	dates;
	t_values	**maptrix;

	ft_bzero(&dates, sizeof(dates));
	select_map(&dates);
	if (know_dates(&dates) == 0)
	{
		i = 0;
		maptrix = malloc(sizeof(maptrix) * dates.rows);
		while (i < dates.rows)
			maptrix[i++] = malloc(sizeof(maptrix) * dates.columns);
		if (charge_map(maptrix, dates) == 0)
		{
			ft_printf("Columnas: %d\n", dates.columns);
			ft_printf("Filas: %d\n", dates.rows);
			start_draw(maptrix, dates);
		}
		else
			ft_printf("Error!");
		liberate_map(&maptrix, &dates);
		return (0);
	}
	ft_printf("Error!");
	return (0);
}
