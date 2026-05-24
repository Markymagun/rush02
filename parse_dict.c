/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:18:51 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 16:18:51 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

void	*free_dict_err(t_dict *dict, int count, int fd)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(dict[i].key);
		free(dict[i].value);
		i++;
	}
	free(dict);
	close(fd);
	return (NULL);
}

static t_dict	*finish_read(t_dict *dict, char *l, int i, int li)
{
	if (i > 0 && l[0] != '\0')
	{
		l[i] = '\0';
		if (!parse_line(l, &dict[li++]))
			return (NULL);
	}
	dict[li].key = NULL;
	return (dict);
}

static t_dict	*read_lines(t_dict *dict, int fd, int *size)
{
	char	l[4096];
	int		i;
	int		li;

	i = 0;
	li = 0;
	while (read(fd, &l[i], 1) > 0)
	{
		if (l[i] == '\n')
		{
			l[i] = '\0';
			if (l[0] != '\0' && !parse_line(l, &dict[li++]))
				return (free_dict_err(dict, li - 1, fd));
			i = -1;
		}
		if (i < 4095)
			i++;
	}
	close(fd);
	if (!finish_read(dict, l, i, li))
		return (free_dict_err(dict, li, fd));
	if (i > 0 && l[0] != '\0')
		li++;
	return (*size = li, dict);
}

static t_dict	*init_dict(char *file_path, int *size, int *fd)
{
	t_dict	*dict;

	*size = count_lines(file_path);
	if (*size <= 0)
		return (NULL);
	dict = malloc(sizeof(t_dict) * (*size + 1));
	if (!dict)
		return (NULL);
	*fd = open(file_path, O_RDONLY);
	if (*fd < 0)
	{
		free(dict);
		return (NULL);
	}
	return (dict);
}

t_dict	*parse_dict(char *file_path, int *size)
{
	int		fd;
	t_dict	*dict;

	dict = init_dict(file_path, size, &fd);
	if (!dict)
		return (NULL);
	return (read_lines(dict, fd, size));
}
