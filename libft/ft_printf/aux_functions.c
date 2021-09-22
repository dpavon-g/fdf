/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_auxFunctions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:28:06 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/07/29 19:28:08 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	show_string(int *length, char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		ft_putchar_fd(string[i], 1);
		(*length)++;
		i++;
	}
}

int	ft_len_final(unsigned long num, int base)
{
	int	i;

	i = 0;
	if (num == 0)
	{
		i++;
		return (i);
	}
	while (num > 0)
	{
		i++;
		num /= base;
	}
	return (i);
}

char	*ft_transform_number(unsigned long num, int type, int base)
{
	int		len;
	char	*number;
	char	*string;

	number = NULL;
	if (type == 0)
		string = ft_strdup("0123456789ABCDEF");
	else
		string = ft_strdup("0123456789abcdef");
	len = ft_len_final(num, base);
	number = (char *)malloc(sizeof(char) * len + 1);
	number[len] = '\0';
	len--;
	while (len >= 0)
	{
		number[len] = string[num % base];
		num /= base;
		len--;
	}
	free(string);
	return (number);
}

int	str_spaces2(int *length, t_printf *content, char *str, int len)
{
	int		position;
	char	value;

	position = 0;
	if (content->zero == 1 && content->less == 0)
	{
		value = '0';
		if (str[0] == '-')
		{
			ft_putchar_fd('-', 1);
			(*length)++;
			position++;
		}
	}
	else
		value = ' ';
	while (content->width > len && content->width > content->precision)
	{
		ft_putchar_fd(value, 1);
		content->width--;
		(*length)++;
	}
	return (position);
}

int	str_spaces(int *length, t_printf *content, char *str)
{
	int		len;
	int		position;

	position = 0;
	len = (int)ft_strlen(str);
	if (content->precision != -1)
	{
		if (str[0] == '-' && content->precision >= len)
			content->width--;
		while (content->width > len && content->width > content->precision)
		{
			ft_putchar_fd(' ', 1);
			content->width--;
			(*length)++;
		}
	}
	else
		position = str_spaces2(length, content, str, len);
	return (position);
}
