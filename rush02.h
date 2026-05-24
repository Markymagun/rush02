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

int	get_inputs(int argc, char **argv, char **dict_file, char **num_str);
int	check_invalid_input(char *argv);
char	*get_val(char *str);
int		free_key_err(char *key);
void	*free_dict_err(t_dict *dict, int count, int fd);
int		parse_line(char *line, t_dict *entry);
void	run_standard_input_mode(char *dict_file);
void	run_normal_mode(char *dict_file, char *num_str);
char	*find_in_dict(t_dict *dict, int size, char *key);
int	print_three_digits(t_dict *dict, int size, char *str);

#endif

