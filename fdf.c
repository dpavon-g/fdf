/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pavon <pavon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/27 09:57:00 by pavon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	number_columns(char **string)
{
	int		i;
	char	**the_split;

	i = 0;
	the_split = ft_split(*string, ' ');
	while (the_split[i] != NULL)
	{
		free(the_split[i]);
		i++;
	}
	free(the_split);
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

int	get_number(char letter)
{
	if (letter >= '0' && letter <= '9')
		return (letter - 48);
	else if (letter == 'A')
		return (10);
	else if (letter == 'B')
		return (11);
	else if (letter == 'C')
		return (12);
	else if (letter == 'D')
		return (13);
	else if (letter == 'E')
		return (14);
	else if (letter == 'F')
		return (15);
	else
		return (-1);
}

int	get_color(char *str)
{
	int	number;
	int	len;
	int	position;
	int	i;
	int	actual_number;
	
	position = 1;
	number = 2;
	len = ft_strlen(str);
	len--;
	while (str[len] != ',')
	{
		i = 0;
		actual_number = get_number(str[len]);
		while (position > i)
		{
			actual_number *= 16;
			i++;
		}
		position++;
		len--;
	}
	ft_printf("%d\n", actual_number);
	return (number);
}

int	charge_map(t_values **maptrix, t_gdates numbers)
{
	int		fd;
	char	*string;
	int		x;
	char	**the_split;
	int		y;

	y = 0;
	fd = open(numbers.map, O_RDONLY);
	while (y < numbers.rows)
	{
		x = 0;
		get_next_line(fd, &string);
		the_split = ft_split(string, ' ');
		while (x < numbers.columns)
		{
			maptrix[y][x].number = ft_atoi(the_split[x]);
			if (ft_strchr(the_split[x], ',') != 0)
				maptrix[y][x].color = get_color(the_split[x]);
			else
				maptrix[y][x].color = 16777215;
			free(the_split[x]);
			x++;
		}
		y++;
		free(the_split);
		free(string);
	}
	ft_printf("Number: %d\n", maptrix[0][0].number);
	ft_printf("Color: %d\n", maptrix[0][0].color);
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
