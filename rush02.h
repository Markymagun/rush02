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
void	run_standard_input_mode(char *dict_file);
void	run_normal_mode(char *dict_file, char *num_str);

#endif
