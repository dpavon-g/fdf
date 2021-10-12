/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpavon-g <dpavon-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 18:49:44 by dpavon-g          #+#    #+#             */
/*   Updated: 2021/10/08 11:55:22 by dpavon-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_svreserve(char **sv, char *buf)
{
	char	*aux;

	if (!*sv)
		*sv = ft_strdup2(buf);
	else
	{
		aux = *sv;
		*sv = ft_strjoin2(*sv, buf);
		free(aux);
	}
}

int	ft_fill(char **sv, char *buf, int BUFFER, int fd)
{
	char	*aux;
	int		status;

	aux = ft_strdup2(*sv);
	free(*sv);
	*sv = NULL;
	status = read(fd, buf, BUFFER);
	buf[status] = '\0';
	if (status != 0)
	{
		*sv = ft_strjoin2(aux, buf);
		free(aux);
	}
	else if (status == 0)
	{
		*sv = ft_strdup2(aux);
		free(aux);
	}
	return (status);
}

void	ft_exit(char **sv, char ***line)
{
	char	*aux;
	char	*ptr;
	int		i;

	i = 0;
	while ((*sv)[i] != '\n')
		i++;
	aux = malloc(i + 1 * (sizeof(char)));
	i = 0;
	while ((*sv)[i] != '\n')
	{
		aux[i] = (*sv)[i];
		i++;
	}
	aux[i] = '\0';
	**line = ft_strdup2(aux);
	free(aux);
	ptr = (ft_strchr2(*sv, '\n'));
	ptr++;
	aux = ft_strdup2(ptr);
	free(*sv);
	*sv = ft_strdup2(aux);
	free(aux);
}

void	ft_null(char ***line, char **sv)
{
	**line = ft_strdup2(*sv);
	free(*sv);
	*sv = NULL;
}

int	get_next_line(int fd, char **line)
{
	static char	*sv[4096];
	char		buf[BUFFER_SIZE + 1];
	int			status;

	status = read(fd, buf, BUFFER_SIZE);
	if (status == -1 || BUFFER_SIZE < 1 || !line)
		return (-1);
	buf[status] = '\0';
	ft_svreserve(&sv[fd], buf);
	while (ft_strchr2(sv[fd], '\n') == 0 && status != 0)
		status = ft_fill(&sv[fd], buf, BUFFER_SIZE, fd);
	if (status != 0)
		ft_exit(&sv[fd], &line);
	else
	{	
		if (ft_strchr2(sv[fd], '\n'))
		{
			ft_exit(&sv[fd], &line);
			status = 1;
		}
		else
			ft_null(&line, &sv[fd]);
		return (status);
	}
	return (1);
}
