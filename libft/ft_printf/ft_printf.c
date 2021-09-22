/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:44:16 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/07/29 19:44:18 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	string_space(int *length, t_printf *content, char *str)
{
	int	len;

	len = (int)ft_strlen(str);
	if (content->precision < len && content->precision > -1)
		len = content->precision;
	while (content->width > len)
	{
		(*length)++;
		ft_putchar_fd(' ', 1);
		len++;
	}
}

void	string_precision(int *length, t_printf *content, char *str)
{
	int	len;
	int	i;

	len = content->precision;
	i = 0;
	if (content->less == 0)
		string_space(length, content, str);
	if (len == -1)
		show_string(length, str);
	while (len > 0 && str[i])
	{
		ft_putchar_fd(str[i], 1);
		(*length)++;
		len--;
		i++;
	}
	if (content->less == 1)
		string_space(length, content, str);
}

int	specify(const char *str, int *length, va_list ap)
{
	int			i;
	t_printf	content;

	ft_bzero(&content, sizeof(content));
	content.precision = -1;
	i = 0;
	i += specify_flag(&str[i], length, &content, ap);
	return (i);
}

int	travel(va_list ap, const char *str)
{
	int	i;
	int	length;

	length = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			length++;
			i++;
		}
		else
		{
			i++;
			i += specify(&str[i], &length, ap);
		}
	}
	return (length);
}

int	ft_printf(const char *str, ...)
{
	int	total;

	total = 0;
	va_list(ap);
	va_start(ap, str);
	total += travel(ap, str);
	va_end(ap);
	return (total);
}
