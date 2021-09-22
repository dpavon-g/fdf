/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:10:13 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/04/30 17:34:46 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
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

char	*ft_strdup(const char *s1)
{
	size_t	len;
	void	*ptr;

	len = ft_strlen((char *)s1) + 1;
	ptr = (char *)malloc(len * (sizeof(char)));
	if (ptr == NULL)
		return (NULL);
	return (ft_memcpy(ptr, s1, len));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		s1len;
	int		s2len;

	if (!s1 || !s2)
		return (NULL);
	ptr = malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1));
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	if (ptr)
	{
		ft_memcpy(ptr, s1, s1len);
		ft_memcpy(ptr + s1len, s2, ft_strlen((char *)s2) + 1);
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = c;
	if (ch == '\0')
	{
		s = s + ft_strlen((char *)s);
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
