#include "rush02.h"

char	*find_in_dict(t_dict *dict, int size, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (dict[i].key[j] && key[j] && dict[i].key[j] == key[j])
			j++;
		if (dict[i].key[j] == '\0' && key[j] == '\0')
			return (dict[i].value);
		i++;
	}
	return (NULL);
}

static int	print_hundreds(t_dict *dict, int size, char *str)
{
	char	tmp[2];
	char	*res;

	if (str[0] != '0')
	{
		tmp[0] = str[0];
		tmp[1] = '\0';
		res = find_in_dict(dict, size, tmp);
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
		write(1, " ", 1);
		res = find_in_dict(dict, size, "100");
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
		if (str[1] != '0' || str[2] != '0')
			write(1, " ", 1);
	}
	return (1);
}

static int	print_teens(t_dict *dict, int size, char *str)
{
	char	tmp[3];
	char	*res;

	tmp[0] = str[1];
	tmp[1] = str[2];
	tmp[2] = '\0';
	res = find_in_dict(dict, size, tmp);
	if (!res)
		return (0);
	write(1, res, ft_strlen(res));
	return (1);
}

static int	print_tens_and_units(t_dict *dict, int size, char *str)
{
	char	tmp[3];
	char	*res;

	if (str[1] != '0')
	{
		tmp[0] = str[1];
		tmp[1] = '0';
		tmp[2] = '\0';
		res = find_in_dict(dict, size, tmp);
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
		if (str[2] != '0')
			write(1, " ", 1);
	}
	if (str[2] != '0')
	{
		tmp[0] = str[2];
		tmp[1] = '\0';
		res = find_in_dict(dict, size, tmp);
		if (!res)
			return (0);
		write(1, res, ft_strlen(res));
	}
	return (1);
}

int	print_three_digits(t_dict *dict, int size, char *str)
{
	if (!print_hundreds(dict, size, str))
		return (0);
	if (str[1] == '1')
	{
		if (!print_teens(dict, size, str))
			return (0);
	}
	else
	{
		if (!print_tens_and_units(dict, size, str))
			return (0);
	}
	return (1);
}
