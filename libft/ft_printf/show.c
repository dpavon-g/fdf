/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:30:23 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/07/29 19:30:25 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	final_number(int *length, t_printf *content, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = (int)ft_strlen(str);
	if (str[i] == '-')
	{
		i++;
		ft_putchar_fd('-', 1);
		(*length)++;
		len--;
	}
	while (content->precision > len)
	{
		ft_putchar_fd('0', 1);
		(*length)++;
		len++;
	}
	show_string(length, &str[i]);
}

void	show_number(int *length, int num, t_printf *content)
{
	char	*str;
	int		i;

	i = 0;
	if (num == 0 && content->precision == 0)
		str = ft_strdup("");
	else
		str = ft_itoa(num);
	if (content->less == 0)
	{	
		i = str_spaces(length, content, str);
		final_number(length, content, &str[i]);
	}
	else
	{
		final_number(length, content, str);
		str_spaces(length, content, str);
	}
	free(str);
}

void	digits(int *length, va_list ap, t_printf *content)
{
	int	num;

	num = va_arg(ap, int);
	if (content->have_space == 1)
	{
		ft_putchar_fd(' ', 1);
		(*length)++;
	}
	show_number(length, num, content);
}

void	show_space(t_printf *content, int *length, int len)
{
	while (content->width > len)
	{
		ft_putchar_fd(' ', 1);
		(*length)++;
		content->width--;
	}
}

void	characters(int *length, va_list ap, t_printf *content)
{
	char	character;

	character = va_arg(ap, int);
	if (content->less == 0)
	{
		(*length)++;
		show_space(content, length, 1);
		ft_putchar_fd(character, 1);
	}
	else
	{
		(*length)++;
		ft_putchar_fd(character, 1);
		show_space(content, length, 1);
	}
}
