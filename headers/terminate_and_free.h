#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

# include "main.h"

void	terminate_program(int error, t_data *data);
void	free_data(t_data *data);
void	free_commands(t_cmd *commands);

#endif