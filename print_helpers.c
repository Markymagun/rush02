/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:51:22 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 16:51:22 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	write_space_or_comma(t_dict *dict)
{
	if (dict[0].is_en)
		write(1, ", ", 2);
	else
		write(1, " ", 1);
}

char	*find_dict_safe(t_dict *dict, int size, char *key, char check_char)
{
	if (check_char != '0')
		return (find_in_dict(dict, size, key));
	return (NULL);
}
