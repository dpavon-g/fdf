#include "fdf.h"
#include <fcntl.h>

char	**read_map()
{
	char		*string;
	char		**dates;
	int			length;
	int			status;
	int			fd;

	fd = open("maps/10-2.fdf", O_RDONLY);
	status = get_next_line(fd, &string);
	dates = ft_split(string, ' ');
	ft_printf("String: %s\n", string);

	length = 0;
	while (dates[length] != '\0')
	{
		ft_printf("%s\n", dates[length]);
		length++;
	}

	free(string);
	return (dates);
}

int number_columns(char **string)
{
	int	i;
	char **split;

	i = 0;
	split = ft_split(*string, ' ');
	while (split[i] != '\0')
	{
		free(split[i]);
		i++;
	}
	free(split);
	free(*string);
	return (i);
}

int	know_dates(t_gdates *numbers, char *map)
{
	int		fd;
	int		status;
	char	*string;
	int		flag;

	flag = 0;
	fd = open(map, O_RDONLY);
	status = get_next_line(fd, &string);
	if (status >= 0)
	{
		numbers->columns = number_columns(&string);
		numbers->rows++;
		while (status > 0)
		{
			status = get_next_line(fd, &string);
			free(string);

		}
	}
	if (status < 0)
		flag = 1;
	return (flag);
}

int main()
{
	//char	**dates;
	t_gdates numbers;

	ft_bzero(&numbers, sizeof(numbers));
	know_dates(&numbers, "maps/10-2.fdf");
	ft_printf("Columns: %d\n", numbers.columns);
	//ft_printf("Filas: %d\n", numbers.rows);
	//dates = read_map();
	//ft_printf("%s\n", dates[0]);
	//free(dates);
	//system("leaks fdf");
	return (0);
}