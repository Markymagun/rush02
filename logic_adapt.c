#include "rush02.h"

static char	*make_suffix(int zero_count)
{
	char	*key;
	int		i;

	key = malloc(sizeof(char) * (zero_count + 2));
	if (!key) return (NULL);
	key[0] = '1';
	i = 1;
	while (i <= zero_count)
		key[i++] = '0';
	key[i] = '\0';
	return (key);
}

static void	get_chunk(char *num_str, char *chunk, int len, int groups)
{
	int	start;
	int	c;

	start = len - (groups * 3);
	c = 0;
	while (c < 3)
	{
		if (start < 0) chunk[c] = '0';
		else chunk[c] = num_str[start];
		start++;
		c++;
	}
	chunk[3] = '\0';
}

static int	process_group(t_dict *dict, int size, char *chunk, int groups)
{
	char	*suf;
	char	*s_key;

	if (!(chunk[0] == '0' && chunk[1] == '0' && chunk[2] == '0'))
	{
		if (!print_three_digits(dict, size, chunk)) return (0);
		if (groups > 1)
		{
			s_key = make_suffix((groups - 1) * 3);
			suf = find_in_dict(dict, size, s_key);
			free(s_key);
			if (!suf) return (0);
			write(1, " ", 1);
			write(1, suf, ft_strlen(suf));
		}
	}
	return (1);
}

void	run_normal_mode(t_dict *dict, int size, char *num_str)
{
	int		groups;
	int		max_g;
	char	chunk[4];

	if (num_str[0] == '0' && num_str[1] == '\0')
	{
		if (find_in_dict(dict, size, "0"))
			write(1, find_in_dict(dict, size, "0"), ft_strlen(find_in_dict(dict, size, "0")));
		write(1, "\n", 1);
		return ;
	}
	max_g = (ft_strlen(num_str) + 2) / 3;
	groups = max_g;
	while (groups > 0)
	{
		get_chunk(num_str, chunk, ft_strlen(num_str), groups);
		if (groups < max_g && !(chunk[0] == '0' && chunk[1] == '0' && chunk[2] == '0'))
			write(1, " ", 1);
		if (!process_group(dict, size, chunk, groups))
		{ write(1, "Dict Error\n", 11); return ; }
		groups--;
	}
	write(1, "\n", 1);
}

void	run_standard_input_mode(t_dict *dict, int size)
{
	char	buf;
	int		i;
	char	input[4096];

	i = 0;
	while (read(0, &buf, 1) > 0)
	{
		if (buf == '\n')
		{
			input[i] = '\0';
			if (check_invalid_input(input) != 0)
				run_normal_mode(dict, size, input);
			i = 0;
		}
		else
		{
			if (i < 4095)
				input[i++] = buf;
		}
	}
}
