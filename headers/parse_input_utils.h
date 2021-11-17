#ifndef PARSE_INPUT_UTILS_H
# define PARSE_INPUT_UTILS_H

# include "main.h"

int		skip_white_space(char *input);
int	is_a_valid_command(t_data *data, char *cmd);
int	is_in_dir(char *input, char *path, DIR *directory);

#endif