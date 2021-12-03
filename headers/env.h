#ifndef ENV_H
# define ENV_H

#include "types.h"

t_pair	*build_var_pair(char *envp_var);

t_env	ft_init_env(char **envp);

bool	is_env_var(t_env *env, char *key);

void	print_env_vars(t_list *env, int *ctx);

int		update_env_var(char *key, char *new_value);

char	*get_env_var(char *key);

#endif // !ENV_H