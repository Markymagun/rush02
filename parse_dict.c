#include "rush02.h"

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

// 📦 แยกฟังก์ชันดึงบรรทัดออกมา เพื่อรักษา The Norm
static t_dict	*read_lines(t_dict *dict, int fd)
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
		i++;
	}
	close(fd);
	dict[li].key = NULL;
	return (dict);
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
	return (read_lines(dict, fd)); // ส่งไปให้ลูปอ่านไฟล์ทำงาน
}
