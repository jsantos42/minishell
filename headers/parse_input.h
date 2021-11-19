#ifndef PARSE_INPUT_H
# define PARSE_INPUT_H

# include "main.h"

# define NEW_ARG	1
# define NULLTERM	1

int		parse_input(t_data *data);
void	read_cmd_and_args(t_data *data, t_leaf_node *current_node, int *i);
void	read_argument(t_data *data, t_leaf_node *current_node, int *i);
void	save_new_argument(t_leaf_node *current_node, char *new_arg);

#endif