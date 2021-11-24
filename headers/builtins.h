#ifndef BUILTINS_H
# define BUILTINS_H

# include "main.h"

void	exec_builtin(t_leaf_node *leaf);

bool	is_builtin(char *cmd);

void	builtin_echo(char **args);

#endif // !BUILTINS_H