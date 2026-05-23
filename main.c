#include "rush02.h"

int	main(int argc, char **argv)
{
	char	*dict_file;
	char	*num_str;
	int		mode;

	mode = get_inputs(argc, argv, &dict_file, &num_str);
	if (mode == 1)
	{
		run_standard_input_mode(dict_file);
	}
	else if (mode == 2)
	{
		run_normal_mode(dict_file, num_str);
	}
	else
	{
		write(1, "Error\n", 6);
		return (1);
	}
	return (0);
}
