#include "rush02.h"

int	count_lines(char *file_path)
{
	int		fd;
	int		lines;
	char	buf;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	lines = 0;
	while (read(fd, &buf, 1) > 0)
	{
		if (buf == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}

static char	*get_val(char *str)
{
	int		i;
	int		len;
	char	*val;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	len = 0;
	while (str[i + len] != '\0' && str[i + len] != '\n')
		len++;
	val = malloc(sizeof(char) * (len + 1));
	if (!val)
		return (NULL);
	len = 0;
	while (str[i] != '\0' && str[i] != '\n')
		val[len++] = str[i++];
	val[len] = '\0';
	return (val);
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
		return (0);
	entry->value = get_val(&line[i + 1]);
	if (!entry->value)
		return (0);
	return (1);
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
	char	line[4096];
	int		i;
	int		li;
	t_dict	*dict;

	dict = init_dict(file_path, size, &fd);
	if (!dict)
		return (NULL);
	i = 0;
	li = 0;
	while (read(fd, &line[i], 1) > 0)
	{
		if (line[i] == '\n')
		{
			line[i] = '\0';
			if (line[0] != '\0' && !parse_line(line, &dict[li++]))
				return (NULL);
			i = -1;
		}
		i++;
	}
	close(fd);
	dict[li].key = NULL;
	return (dict);
}
