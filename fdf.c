/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:04:22 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/09/22 14:38:22 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

// char	**read_map()
// {
// 	char		*string;
// 	char		**dates;
// 	int			length;
// 	int			status;
// 	int			fd;

// 	fd = open("maps/10-2.fdf", O_RDONLY);
// 	status = get_next_line(fd, &string);
// 	dates = ft_split(string, ' ');
// 	ft_printf("String: %s\n", string);

// 	length = 0;
// 	while (dates[length] != '\0')
// 	{
// 		ft_printf("%s\n", dates[length]);
// 		length++;
// 	}

// 	free(string);
// 	return (dates);
// }

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

int	know_dates(t_gdates *numbers, char *map)
{
	int		fd;
	int		status;
	char	*string;
	int		flag;

	flag = 0;
	fd = open(map, O_RDONLY);
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

int	read_map(t_values ***maptrix, t_gdates *numbers)
{
	int i;

	i = 0;
	*maptrix = malloc(sizeof(maptrix) * numbers->rows);
	while (i < numbers->rows)
	{
		maptrix[i] = malloc(sizeof(maptrix) * numbers->columns);
		i++;
	}
	return (0);
}

int	main(void)
{
	int			flag;
	t_gdates	numbers;
	t_values	**maptrix;
	
	ft_bzero(&numbers, sizeof(numbers));
	flag = know_dates(&numbers, "maps/10-2.fdf");
	if (flag == 0 && read_map(&maptrix, &numbers) == 0)
	{
		ft_printf("Map loaded!!");
		free(maptrix);
	}
	if (flag == 1)
		ft_printf("Error!");
	//system("leaks fdf");
	return (0);
}
