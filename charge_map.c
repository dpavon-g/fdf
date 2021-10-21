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
	if (letter1 >= 'a' && letter1 <= 'f')
		string = ft_strdup("0123456789abcdef");
	else
		string = ft_strdup("0123456789ABCDEF");
	while (letter1 != string[i] && i < 16)
		i++;
	num1 = i;
	free(string);
	i = 0;
	if (letter2 >= 'a' && letter2 <= 'f')
		string = ft_strdup("0123456789abcdef");
	else
		string = ft_strdup("0123456789ABCDEF");
	while (letter2 != string[i] && i < 16)
		i++;
	num2 = i;
	free(string);
	return ((num1 * 16) + num2);
}

void	rgb_to_decimal(int *r, int *b, int *g, char *string)
{
	int		i;
	int		l;
	char	*str;

	l = 5;
	str = malloc(sizeof(char) * 7);
	str[6] = '\0';
	i = ft_strlen(string) - 1;
	while (string[i] != 'x')
		str[l--] = string[i--];
	if (l > 0)
	{
		while (l >= 0)
			str[l--] = '0';
	}
	*r = get_number(str[0], str[1]);
	*b = get_number(str[2], str[3]);
	*g = get_number(str[4], str[5]);
	free(str);
}

int	get_color(char *str)
{
	int		r;
	int		g;
	int		b;
	char	*string;

	string = ft_strdup(ft_strchr(str, ','));
	rgb_to_decimal(&r, &b, &g, string);
	free(string);
	return (0 << 24 | r << 16 | g << 8 | b);
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

void	save_map(t_vector	coord, t_values **maptrix, t_gdates dates, int fd)
{
	char	*string;
	char	**the_split;

	coord.x = 0;
	get_next_line(fd, &string);
	the_split = ft_split(string, ' ');
	while (coord.x < dates.columns)
	{
		if (is_digit(the_split[coord.x]) == 1)
		{
			maptrix[coord.y][coord.x].number = ft_atoi(the_split[coord.x]);
			maptrix[coord.y][coord.x].color = 16777215;
		}
		else if (good_value(the_split[coord.x]) == 1)
		{
			maptrix[coord.y][coord.x].number = ft_atoi(the_split[coord.x]);
			maptrix[coord.y][coord.x].color = get_color(the_split[coord.x]);
			//ft_printf("Color: %d\n", maptrix[coord.y][coord.x].color);
		}
		else
			dates.flag = 1;
		free(the_split[coord.x]);
		coord.x++;
	}
	free(the_split);
	free(string);
}

int	charge_map(t_values **maptrix, t_gdates dates)
{
	int			fd;
	t_vector	coord;

	dates.flag = 0;
	coord.y = 0;
	fd = open(dates.map, O_RDONLY);
	while (coord.y < dates.rows)
	{
		save_map(coord, maptrix, dates, fd);
		coord.y++;
	}
	//Tengo que mirar mañana la conversion de los colores porque no me está convirtiendo bien las cosas
	return (dates.flag);
}
