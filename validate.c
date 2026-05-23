#include "rush02.h"

static int	input_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	check_mode(char *str)
{
	if (str[0] == '-' && input_len(str) == 1)
		return (1);
	return (0);
}

static int	check_invalid_input(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '0' && input_len(argv) > 1)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	while (argv[i] != '\0')
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

int	get_inputs(int argc, char **argv, char **dict_file, char **num_str)
{
	if (argc < 2 || argc > 3)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	if (argc == 2)
	{
		*dict_file = "numbers.dict";
		*num_str = argv[1];
	}
	else
	{
		*dict_file = argv[1];
		*num_str = argv[2];
	}
	if (check_mode(*num_str) == 1)
		return (1);
	if (check_invalid_input(*num_str) == 0)
		return (0);
	return (2);
}
