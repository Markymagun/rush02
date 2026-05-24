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

static int	get_val_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] < 9 || str[i] > 13))
		str++;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

int	parse_line(char *line, t_dict *entry)
{
	int	i;
	int	k;

	i = 0;
	while (line[i] < '0' || line[i] > '9')
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
	while (line[i] == ' ' || (line[i] < 9 || line[i] > 13))
		i++;
	if (line[i] != ':')
		return (0);
	return (1);
}
