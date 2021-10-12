/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:03:51 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/08 11:55:07 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
int		ft_fill(char **sv, char *buf, int BUFFER, int fd);
char	*ft_strdup2(const char *s1);
void	*ft_memcpy2(void *dst, const void *src, size_t n);
char	*ft_strjoin2(char const *s1, char const *s2);
char	*ft_strchr2(const char *s, int c);
size_t	ft_strlen2(const char *str);

#endif
