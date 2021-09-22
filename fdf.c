/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/22 15:26:15 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	number_columns(char **string)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(*string, ' ');
	while (split[i] != '\0')
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(*string);
	return (i);
}

int	know_dates(t_gdates *numbers)
{
	int		fd;
	int		status;
	char	*string;
	int		flag;

	flag = 0;
	fd = open(numbers->map, O_RDONLY);
	status = get_next_line(fd, &string);
	if (status >= 0)
	{
		numbers->columns = number_columns(&string);
		numbers->rows++;
		while (status > 0)
		{
			status = get_next_line(fd, &string);
			numbers->rows++;
			if (string[0] == '\0')
				numbers->rows--;
			if (number_columns(&string) != numbers->columns && status > 0)
				flag = 1;
		}
	}
	if (status < 0)
		flag = 1;
	return (flag);
}

int	charge_map(t_values **maptrix, t_gdates numbers)
{
	int	fd;
	char *string;
	int x;
	char **split;
	int	y;

	y = 0;
	fd = open(numbers.map, O_RDONLY);
	while (y < numbers.rows)
	{
		x = 0;
		get_next_line(fd, &string);
		split = ft_split(string, ' ');
		while (x < numbers.columns)
		{
			maptrix[y][x].number = ft_atoi(split[x]);
			free(split[x]);
			x++;
		}
		y++;
		free(split);
		free(string);
	}
	ft_printf("Number: %d\n", maptrix[0][0].color);
	return (0);
}

int	main(void)
{
	int			flag;
	t_gdates	numbers;
	t_values	**maptrix;
	int			i;
	
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
	//system("leaks fdf");
	return (0);
}
