#ifndef PARSE_INPUT_UTILS_H
# define PARSE_INPUT_UTILS_H

# include "main.h"

void	skip_white_space(char *input, int *i);
void	save_new_argument(t_leaf_node *current_node, char *new_arg);

#endif