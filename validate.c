/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:19:22 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 16:19:23 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static int	check_mode(char *str)
{
	if (str[0] == '-' && ft_strlen(str) == 1)
		return (1);
	return (0);
}

int	check_invalid_input(char *argv)
{
	int	i;

	i = 0;
	if (argv[i] == '0' && ft_strlen(argv) > 1)
	{
		return (0);
	}
	while (argv[i] != '\0')
	{
		if (argv[i] < '0' || argv[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	get_inputs(int argc, char **argv, char **dict_path, char **num_str)
{
	if (argc < 2 || argc > 3)
	{
		return (0);
	}
	if (argc == 2)
	{
		*dict_path = "numbers.dict";
		*num_str = argv[1];
	}
	else
	{
		*dict_path = argv[1];
		*num_str = argv[2];
	}
	if (check_mode(*num_str) == 1)
		return (1);
	if (check_invalid_input(*num_str) == 0)
		return (0);
	return (2);
}
