#ifndef COMMAND_UTILS_H
# define COMMAND_UTILS_H

# include "main.h"

int	is_exit_command(char *input);
int	is_a_valid_command(t_data *data, char *cmd);
int	is_in_dir(t_data *data, char *input, char *path, DIR *directory);
void	execute_command(t_data *data);

#endif