/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:53:35 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:57:23 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	good_value(char *str)
{
	int		i;
	char	*string;
	int		flag;

	flag = 1;
	i = 0;
	if (ft_strchr(str, ',') == 0)
		return (0);
	else
		string = ft_strdup(ft_strchr(str, ','));
	while (str[i] != ',')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (string[0] != ',' || string[1] != '0' || string[2] != 'x')
		flag = 0;
	free(string);
	return (flag);
}
