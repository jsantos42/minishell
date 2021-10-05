#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "main.h"

int	is_exit_command(char *input);
int	is_a_valid_command(char *input, char **paths);
int	is_in_dir(char *input, DIR *directory);

#endif