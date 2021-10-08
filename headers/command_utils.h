#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "main.h"

int	is_exit_command(char *input);
int	is_a_valid_command(char *cmd, t_data *data);
int	is_in_dir(char *input, char *path, DIR *directory);
void	execute_command(t_data *data);

#endif