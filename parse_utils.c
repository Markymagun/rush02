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
	val = malloc(sizeof(char) * (len + 1));
	if (!val)
		return (NULL);
	len = 0;
	while (str[i] != '\0' && str[i] != '\n')
		val[len++] = str[i++];
	val[len] = '\0';
	return (val);
}

// 🧽 ทีมทำความสะอาด 1: ใช้ลบ Key กรณีบรรทัดนั้นพังครึ่งทาง
int	free_key_err(char *key)
{
	free(key);
	return (0);
}

// 🧽 ทีมทำความสะอาด 2: ใช้ลบ Dictionary ทั้งเล่ม กรณีไฟล์พังกลางคัน
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
