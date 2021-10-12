/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:10:13 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/08 11:55:43 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy2(void *dst, const void *src, size_t n)
{
	char			*destino;
	const char		*source;
	int				i;

	i = 0;
	destino = dst;
	source = src;
	if (!dst && !src)
		return (0);
	while (n-- > 0)
	{
		destino[i] = source[i];
		i++;
	}
	return (dst);
}

char	*ft_strdup2(const char *s1)
{
	size_t	len;
	void	*ptr;

	len = ft_strlen2((char *)s1) + 1;
	ptr = (char *)malloc(len * (sizeof(char)));
	if (ptr == NULL)
		return (NULL);
	return (ft_memcpy2(ptr, s1, len));
}

char	*ft_strjoin2(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1len;

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc((ft_strlen2((char *)s1) + ft_strlen2((char *)s2) + 1));
	s1len = ft_strlen2((char *)s1);
	if (ptr)
	{
		ft_memcpy2(ptr, s1, s1len);
		ft_memcpy2(ptr + s1len, s2, ft_strlen2((char *)s2) + 1);
	}
	return (ptr);
}

char	*ft_strchr2(const char *s, int c)
{
	char	ch;

	ch = c;
	if (ch == '\0')
	{
		s = s + ft_strlen2((char *)s);
		return ((char *) s);
	}
	while (*s)
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	return (0);
}
