#ifndef INIT_H
# define INIT_H

# include "main.h"

void	init_data(t_data *data, char **envp);
t_tree	*init_leaf_node(t_tree *previous);
t_tree	*init_branch_node(t_tree *previous);
void	init_history(void);

#endif