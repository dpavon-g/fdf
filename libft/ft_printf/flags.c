/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:16:29 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/07/29 19:16:37 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	specify_flag(const char *str, int *leng, t_printf *content, va_list ap)
{
	int	i;

	i = 0;
	while (ft_strchr(TYPES, str[i]) == 0 && str[i])
	{
		if (str[i] == ' ')
			content->have_space = 1;
		else if (str[i] == '.')
			i += point(&str[i], content, ap);
		else if (str[i] >= '0' && str[i] <= '9')
			i += width(&str[i], content);
		else if (str[i] == '-')
			content->less = 1;
		else if (str[i] == '*')
			apostro(content, ap);
		i++;
	}
	if (str[i] == '\0')
		return (i);
	if (ft_strchr(TYPES, str[i]) != 0)
		specify_type(str[i], content, ap, leng);
	i++;
	return (i);
}

void	specify_type(const char s, t_printf *content, va_list ap, int *length)
{
	if (s == 'd')
		digits(length, ap, content);
	else if (s == 'i')
		digits(length, ap, content);
	else if (s == 'c')
		characters(length, ap, content);
	else if (s == 's')
		string(length, ap, content);
	else if (s == '%')
	{
		ft_putchar_fd('%', 1);
		(*length)++;
	}
	else if (s == 'u')
		unsig_num(length, ap, content);
	else if (s == 'X' || s == 'x')
		hexadecimal(length, ap, content, s);
	else if (s == 'p')
		pointer(length, ap, content);
}

int	point(const char *str, t_printf *content, va_list ap)
{
	int	i;

	i = 1;
	if (str[i] >= '0' && str[i] <= '9')
	{
		content->precision = ft_atoi(&str[i]);
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		i--;
	}
	else if (str[i] == '*')
	{
		content->precision = va_arg(ap, int);
		if (content->precision < 0)
			content->precision = -1;
	}
	else
	{
		content->precision = 0;
		i--;
	}
	return (i);
}

int	width(const char *str, t_printf *content)
{
	int	i;

	i = 0;
	if (str[i] == '0')
		content->zero = 1;
	content->width = ft_atoi(&str[i]);
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	i--;
	return (i);
}

void	apostro(t_printf *content, va_list ap)
{
	content->width = va_arg(ap, int);
	if (content->width < 0)
	{
		content->width *= -1;
		content->less = 1;
	}
}
