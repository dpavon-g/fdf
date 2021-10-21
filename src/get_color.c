/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:54:08 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/21 17:54:09 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_number(char letter1, char letter2)
{
	char	*string;
	int		i;
	int		num1;
	int		num2;

	i = 0;
	if (letter1 >= 'a' && letter1 <= 'f')
		string = ft_strdup("0123456789abcdef");
	else
		string = ft_strdup("0123456789ABCDEF");
	while (letter1 != string[i] && i < 16)
		i++;
	num1 = i;
	free(string);
	i = 0;
	if (letter2 >= 'a' && letter2 <= 'f')
		string = ft_strdup("0123456789abcdef");
	else
		string = ft_strdup("0123456789ABCDEF");
	while (letter2 != string[i] && i < 16)
		i++;
	num2 = i;
	free(string);
	return ((num1 * 16) + num2);
}

void	rgb_to_decimal(int *r, int *b, int *g, char *string)
{
	int		i;
	int		l;
	char	*str;

	l = 5;
	str = malloc(sizeof(char) * 7);
	str[6] = '\0';
	i = ft_strlen(string) - 1;
	while (string[i] != 'x')
		str[l--] = string[i--];
	if (l > 0)
	{
		while (l >= 0)
			str[l--] = '0';
	}
	*r = get_number(str[0], str[1]);
	*b = get_number(str[2], str[3]);
	*g = get_number(str[4], str[5]);
	free(str);
}

int	get_color(char *str)
{
	int		r;
	int		g;
	int		b;
	char	*string;

	string = ft_strdup(ft_strchr(str, ','));
	rgb_to_decimal(&r, &b, &g, string);
	free(string);
	return (0 << 24 | r << 16 | g << 8 | b);
}
