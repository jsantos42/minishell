#ifndef ENV_H
# define ENV_H

#include "types.h"

t_pair	*build_var_pair(char *envp_var);

t_env	ft_init_env(char **envp);

bool	is_env_var(t_env *env, char *key);

void	print_env_vars(t_list *env, int *ctx);

int		update_env_var(char *key, char *new_value);

int		builtin_export(t_data *data, char **args, int *ctx);

void	builtin_env(int *ctx);

char	*get_env_var(char *key);

#endif // !ENV_H