#include "fdf.h"

int	number_columns(char **string)
{
	int		i;
	char	**the_split;

	i = 0;
	the_split = ft_split(*string, ' ');
	while (the_split[i] != NULL)
	{
		free(the_split[i]);
		i++;
	}
	free(the_split);
	free(*string);
	return (i);
}

int	know_dates(t_gdates *numbers)
{
	int		fd;
	int		status;
	char	*string;
	int		flag;

	flag = 0;
	fd = open(numbers->map, O_RDONLY);
	status = get_next_line(fd, &string);
	if (status >= 0)
	{
		numbers->columns = number_columns(&string);
		numbers->rows++;
		while (status > 0)
		{
			status = get_next_line(fd, &string);
			numbers->rows++;
			if (string[0] == '\0')
				numbers->rows--;
			if (number_columns(&string) != numbers->columns && status > 0)
				flag = 1;
		}
	}
	if (status < 0)
		flag = 1;
	return (flag);
}

int	get_number(char letter1, char letter2)
{
	char	*string;
	int		i;
	int		num1;
	int		num2;

	i = 0;
	string = ft_strdup("0123456789ABCDEF");
	while (letter1 != string[i] && i < 16)
		i++;
	num1 = i;
	i = 0;
	while (letter2 != string[i] && i < 16)
		i++;
	num2 = i;
	free(string);
	return ((num1 * 16) + num2);
}

int	get_color(char *str)
{
	int	r;
	int	g;
	int	b;

	r = get_number(str[4], str[5]);
	b = get_number(str[6], str[7]);
	g = get_number(str[8], str[9]);
	return (r << 16 | g << 8 | b);
}

int	charge_map(t_values **maptrix, t_gdates numbers)
{
	int		fd;
	char	*string;
	int		x;
	char	**the_split;
	int		y;

	y = 0;
	fd = open(numbers.map, O_RDONLY);
	while (y < numbers.rows)
	{
		x = 0;
		get_next_line(fd, &string);
		the_split = ft_split(string, ' ');
		while (x < numbers.columns)
		{
			maptrix[y][x].number = ft_atoi(the_split[x]);
			if (ft_strchr(the_split[x], ',') != 0)
				maptrix[y][x].color = get_color(the_split[x]);
			else
				maptrix[y][x].color = 16777215;
			free(the_split[x]);
			x++;
		}
		y++;
		free(the_split);
		free(string);
	}
	return (0);
}