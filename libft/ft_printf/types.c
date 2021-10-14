/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 19:19:35 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/14 15:02:00 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	string(int *length, va_list ap, t_printf *content)
{
	char	*str;

	str = ft_strdup(va_arg(ap, char *));
	if (!str)
	{
		free(str);
		str = ft_strdup("(null)");
	}
	string_precision(length, content, str);
	free(str);
}

void	unsig_num(int *length, va_list ap, t_printf *content)
{
	unsigned int	num;
	char			*str;
	int				i;

	num = va_arg(ap, unsigned int);
	i = 0;
	if (num == 0 && content->precision == 0)
		str = ft_strdup("");
	else
		str = ft_transform_number(num, 1, 10);
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

void	hexadecimal(int *length, va_list ap, t_printf *content, char type)
{
	unsigned int	num;
	char			*str;
	int				i;
	int				k;

	num = va_arg(ap, unsigned int);
	if (type == 'X')
		k = 0;
	else
		k = 1;
	if (num == 0 && content->precision == 0)
		str = ft_strdup("");
	else
		str = ft_transform_number(num, k, 16);
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

void	pointer(int *length, va_list ap, t_printf *content)
{
	unsigned long	num;
	char			*aux;
	char			*string;
	int				i;

	num = va_arg(ap, long);
	aux = ft_transform_number(num, 1, 16);
	string = ft_strjoin("0x", aux);
	free(aux);
	if (content->less == 0)
	{	
		i = str_spaces(length, content, string);
		final_number(length, content, &string[i]);
	}
	else
	{
		final_number(length, content, string);
		str_spaces(length, content, string);
	}
	free(string);
}
