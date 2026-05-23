#include "rush02.h"

static int	check_argument(int argc)
{
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	return (1);
}

static int	input_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_first_char(char *str)
{
	int len;
	
	len = input_len(str);
	if (len > 1)
	{
		if (str[0] == '0')
		{
			write(1, "Error\n", 6);
			return (0);
		}
	}
	return (1);
}

int	check_invalid_input(int argc, char *argv)
{
	int i;

	check_argument(argc);
	i = 0;
	while (argv[i])
	{
		
		if (argv[i] < '0' || argv[i] > '9')
		{
			write(1, "Error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}
