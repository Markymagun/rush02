#include "rush02.h"

static void	free_dict(t_dict *dict)
{
	int	i;

	if (!dict)
		return ;
	i = 0;
	while (dict[i].key != NULL)
	{
		free(dict[i].key);
		if (dict[i].value)
			free(dict[i].value);
		i++;
	}
	free(dict);
}

int	main(int argc, char **argv)
{
	char	*dict_path;
	char	*num_str;
	int		dict_size;
	int		mode;
	t_dict	*dict;

	mode = get_inputs(argc, argv, &dict_path, &num_str);
	if (mode == 0)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	dict = parse_dict(dict_path, &dict_size); // 🌟 โหลดพจนานุกรม
	if (!dict)
	{
		write(1, "Dict Error\n", 11);
		return (1);
	}
	if (mode == 1)
		run_standard_input_mode(dict, dict_size); // 🌟 ส่งตัวแปรที่อัปเดตแล้ว
	else if (mode == 2)
		run_normal_mode(dict, dict_size, num_str); // 🌟 ส่งตัวแปรที่อัปเดตแล้ว
	free_dict(dict); // 🌟 คืนเมมโมรี่
	return (0);
}
