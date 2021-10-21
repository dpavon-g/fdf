/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:43:18 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:49:05 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	save_map(t_vector	coord, t_values **maptrix, t_gdates dates, int fd)
{
	char	*string;
	char	**the_split;

	coord.x = 0;
	get_next_line(fd, &string);
	the_split = ft_split(string, ' ');
	while (coord.x < dates.columns)
	{
		if (is_digit(the_split[coord.x]) == 1)
		{
			maptrix[coord.y][coord.x].number = ft_atoi(the_split[coord.x]);
			maptrix[coord.y][coord.x].color = 16777215;
		}
		else if (good_value(the_split[coord.x]) == 1)
		{
			maptrix[coord.y][coord.x].number = ft_atoi(the_split[coord.x]);
			maptrix[coord.y][coord.x].color = get_color(the_split[coord.x]);
		}
		else
			dates.flag = 1;
		free(the_split[coord.x]);
		coord.x++;
	}
	free(the_split);
	free(string);
}

int	charge_map(t_values **maptrix, t_gdates dates)
{
	int			fd;
	t_vector	coord;

	dates.flag = 0;
	coord.y = 0;
	fd = open(dates.map, O_RDONLY);
	while (coord.y < dates.rows)
	{
		save_map(coord, maptrix, dates, fd);
		coord.y++;
	}
	return (dates.flag);
}
