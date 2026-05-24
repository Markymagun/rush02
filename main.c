/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 17:05:03 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 17:05:04 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	set_dict_grammar_flag(t_dict *dict, int size, int argc)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dict[i].is_en = (argc == 2);
		i++;
	}
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
		return (write(1, "Error\n", 6), 1);
	dict = parse_dict(dict_path, &dict_size);
	if (!dict)
		return (write(1, "Dict Error\n", 11), 1);
	set_dict_grammar_flag(dict, dict_size, argc);
	if (mode == 1)
		run_standard_input_mode(dict, dict_size);
	else if (mode == 2)
		run_normal_mode(dict, dict_size, num_str);
	free_dict(dict);
	return (0);
}
