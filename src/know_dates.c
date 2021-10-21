/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   know_dates.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:53:42 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:53:43 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		return (flag);
	}
	free(numbers->map);
	return (1);
}
