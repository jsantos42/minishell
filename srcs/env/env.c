#include "../../headers/env/env.h"

t_env	ft_init_env(char **envp)
{
	int		iter;
	t_pair	*env_var;
	t_env	env;

	env.nb_vars = -1;
	while (envp[++env.nb_vars])
		;
	env.array = xmalloc(sizeof(char *) * (env.nb_vars + 1), __FILE__, __LINE__);
	env.list = xmalloc(sizeof(t_list *), __FILE__, __LINE__);
	*env.list = NULL;
	iter = -1;
	while (envp[++iter])
	{	
		env_var = build_var_pair(envp[iter]);
		ft_lstadd_back(env.list, ft_lstnew(env_var));
		env.array[iter] = ft_strdup(envp[iter]);
	}
	env.array[iter] = NULL;
	env.envp = envp;
	return (env);
}

t_pair	*build_var_pair(char *envp_var)
{
	t_pair	*var;
	char	**splitted;

	var = xmalloc(sizeof(t_pair), __FILE__, __LINE__);
	splitted = ft_split(envp_var, '=', NULL);
	var->key = splitted[0];
	var->value = splitted[1];
	free(splitted);
	return (var);
}

bool	is_env_var(t_list *env_list, char *key)
{
	t_pair	*var;

	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

int	update_env_var(char *key, char *new_value)
{
	t_list	*env_list;
	char	**env_array;
	t_pair	*var;

	env_list = *(get_data(NULL)->env.list);
	env_array = get_data(NULL)->env.array;
	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if ((!ft_strncmp(var->key, key, ft_strlen(key) + 1)) && new_value)
		{
			free(*env_array);
			*env_array = ft_strnjoin(3, key, "=", new_value);
			if (var->value)
				free(var->value);
			var->value = ft_strdup(new_value);
			return (0);
		}
		env_list = env_list->next;
		env_array++;
	}
	return (1);
}

void	print_env_vars(t_env *env, int *ctx)
{
	int		iter;
	char	*tmp;
	char	**ordered;

	ordered = xmalloc(sizeof(char *) * (env->nb_vars + 1), __FILE__, __LINE__);
	iter = -1;
	while (env->array[++iter])
		ordered[iter] = env->array[iter];
	ordered[iter] = NULL;
	iter = 0;
	while (ordered[iter + 1])
	{
		if (ft_strncmp(ordered[iter], ordered[iter + 1], ft_strlen(ordered[iter])) > 0)
		{
			tmp = ordered[iter];
			ordered[iter] = ordered[iter + 1];
			ordered[iter + 1] = tmp;
			iter = -1;
		}
		iter++;
	}
	iter = -1;
	while(ordered[++iter])
	{
		ft_putstr_fd("declare -x ", ctx[1]);
		ft_putstr_fd(ordered[iter], ctx[1]);
		write(ctx[1], "\n", 1);
	}
	free(ordered);
	ordered = NULL;

	// while (env_list)
	// {
	// 	var = ((t_pair *)env_list->content);
	// 	ft_putstr_fd("declare -x ", ctx[1]);
	// 	ft_putstr_fd(var->key, ctx[1]);
	// 	if (var->value)
	// 	{
	// 		ft_putstr_fd("=", ctx[1]);
	// 		ft_putstr_fd(var->value, ctx[1]);
	// 	}
	// 	write(ctx[1], "\n", 1);
	// 	env_list = env_list->next;
	// }
}

char	*get_env_var(char *key)
{
	t_list	*env_list;
	t_pair	*var;

	env_list = *(get_data(NULL)->env.list);
	while (env_list)
	{
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, key, ft_strlen(key) + 1))
			return (var->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	__export(char **args, int *ctx)
{
	t_pair	*pair;
	t_data	*data;
	int		iter;

	data = get_data(NULL);
	if (!args[1])
	{
		print_env_vars(&data->env, ctx);
		return (0);
	}
	iter = 0;
	while (args[++iter])
	{
		pair = build_var_pair(args[iter]);
		if (is_env_var(*(data->env.list), pair->key))
			update_env_var(pair->key, pair->value);
		else
		{
			ft_lstadd_back(data->env.list, ft_lstnew(pair));
			data->env.array = ft_push_to_matrix(data->env.array, args[iter]);
			data->env.nb_vars++;
		}
	}
	return (0);
}

int	__env(char **args, int *ctx)
{
	t_list	*env_list;
	t_pair	*var;

	(void)args;
	(void)ctx;
	env_list = *(get_data(NULL)->env.list);
	while (env_list)
	{	
		var = ((t_pair *)env_list->content);
		if (var->value)
			printf("%s=%s\n", var->key, var->value);
		env_list = env_list->next;
	}
	return (1);
}

int	__unset(char **args, int *ctx)
{
	t_list	*env_list;
	t_list	*env_list_prev;
	t_pair	*var;
	int		iter;

	(void)ctx;
	env_list_prev = NULL;
	env_list = *(get_data(NULL)->env.list);
	iter = 0;
	while (env_list)
	{	
		var = ((t_pair *)env_list->content);
		if (!ft_strncmp(var->key, args[1], ft_strlen(var->key) + 1))
		{
			env_list_prev->next = env_list->next;
			ft_lstdelone(env_list, del_env_var);
			ft_matrix_del_one(get_data(NULL)->env.array, iter);
			get_data(NULL)->env.nb_vars--;
			return (0);
		}
		env_list_prev = env_list;
		env_list = env_list->next;
		iter++;
	}
	return (1);
}

void	del_env_var(void *env_var_void)
{
	t_pair	*env_var;

	env_var = (t_pair *)env_var_void;
	if (env_var)
	{
		if (env_var->key)
			free(env_var->key);
		if (env_var->value)
			free(env_var->value);
		free(env_var);
	}
}
