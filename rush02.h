#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_dict
{
	char	*key;
	char	*value;
}	t_dict;

int		get_inputs(int argc, char **argv, char **dict_file, char **num_str);
int		check_invalid_input(char *argv);
char	*get_val(char *str);
int		free_key_err(char *key);
void	*free_dict_err(t_dict *dict, int count, int fd);
int		parse_line(char *line, t_dict *entry);

// 🌟 แก้ไข Arguments ให้ตรงกับ logic_adapt.c
void	run_standard_input_mode(t_dict *dict, int size);
void	run_normal_mode(t_dict *dict, int size, char *num_str);

char	*find_in_dict(t_dict *dict, int size, char *key);
int		print_three_digits(t_dict *dict, int size, char *str);

// 🌟 สิ่งที่ต้องเพิ่มเข้ามา (เพราะโดนเรียกใช้จากไฟล์อื่น)
t_dict	*parse_dict(char *file_path, int *size);
int		ft_strlen(char *str); 
int		count_lines(char *file_path);

#endif
