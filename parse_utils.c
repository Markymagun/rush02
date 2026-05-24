/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:18:57 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 16:18:57 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	buf;
	char	last;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	last = '\n';
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			lines++;
		last = buf;
	}
	close(fd);
	if (last != '\n')
		lines++;
	return (lines);
}

char	*get_val(char *str)
{
	int		i;
	int		k;
	int		len;
	char	*val;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	len = 0;
	while (str[i + len] != '\0' && str[i + len] != '\n')
		len++;
	while (len > 0 && (str[i + len - 1] == ' '
			|| (str[i + len - 1] >= 9 && str[i + len - 1] <= 13)))
		len--;
	val = malloc(sizeof(char) * (len + 1));
	if (!val)
		return (NULL);
	k = 0;
	while (k < len)
	{
		val[k] = str[i + k];
		k++;
	}
	val[k] = '\0';
	return (val);
}

int	free_key_err(char *key)
{
	free(key);
	return (0);
}

int	parse_line(char *line, t_dict *entry)
{
	int	i;
	int	k;

	i = 0;
	while (line[i] >= '0' && line[i] <= '9')
		i++;
	if (i == 0)
		return (0);
	entry->key = malloc(sizeof(char) * (i + 1));
	if (!entry->key)
		return (0);
	k = -1;
	while (++k < i)
		entry->key[k] = line[k];
	entry->key[k] = '\0';
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i] != ':')
		return (free_key_err(entry->key));
	entry->value = get_val(&line[i + 1]);
	if (!entry->value)
		return (free_key_err(entry->key));
	return (1);
}
