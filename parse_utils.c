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
	i = 0;
	while (i < len)
	{
		val[i] = str[i];
		i++;
	}
	val[i] = '\0';
	return (val);
}

int	free_key_err(char *key)
{
	free(key);
	return (0);
}

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
