/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprathu <paprathu@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 16:19:13 by paprathu          #+#    #+#             */
/*   Updated: 2026/05/24 16:19:13 by paprathu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH02_H
# define RUSH02_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_dict
{
	char	*key;
	char	*value;
	int		is_en;
}	t_dict;

int		get_inputs(int argc, char **argv, char **dict_file, char **num_str);
int		check_invalid_input(char *argv);
char	*get_val(char *str);
int		free_key_err(char *key);
void	*free_dict_err(t_dict *dict, int count, int fd);
int		parse_line(char *line, t_dict *entry);
void	run_standard_input_mode(t_dict *dict, int size);
void	run_normal_mode(t_dict *dict, int size, char *num_str);
char	*find_in_dict(t_dict *dict, int size, char *key);
int		print_three_digits(t_dict *dict, int size, char *str);
t_dict	*parse_dict(char *file_path, int *size);
int		ft_strlen(char *str);
int		count_lines(char *file_path);
void	write_space_or_comma(t_dict *dict);
int		print_zero_case(t_dict *dict, int size);
int		pre_check_all(t_dict *dict, int size, char *num_str);

#endif
