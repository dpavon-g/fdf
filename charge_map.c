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

/*
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
	if (flag == 1)
		free(numbers->map);
	return (flag);
}
*/

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
		return (flag);
	}
	free(numbers->map);
	return (1);
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

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != '-')
			return (0);
		i++;
	}
	return (1);
}

int	good_value(char *str)
{
	int		i;
	char	*string;
	int		flag;

	flag = 1;
	i = 0;
	if (ft_strchr(str, ',') == 0)
		return (0);
	else
		string = ft_strdup(ft_strchr(str, ','));
	while (str[i] != ',')
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	if (string[0] != ',' || string[1] != '0' || string[2] != 'x')
		flag = 0;
	free(string);
	return (flag);
}

int	charge_map(t_values **maptrix, t_gdates dates)
{
	int		fd;
	char	*string;
	int		x;
	char	**the_split;
	int		y;

	dates.flag = 0;
	y = 0;
	fd = open(dates.map, O_RDONLY);
	while (y < dates.rows)
	{
		x = 0;
		get_next_line(fd, &string);
		the_split = ft_split(string, ' ');
		while (x < dates.columns)
		{
			if (is_digit(the_split[x]) == 1)
				maptrix[y][x].number = ft_atoi(the_split[x]);
			else if (good_value(the_split[x]) == 1)
				maptrix[y][x].number = ft_atoi(the_split[x]);
			else
				dates.flag = 1;
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
	return (dates.flag);
}
