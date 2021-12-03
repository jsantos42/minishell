#include "../headers/main.h"

t_env	ft_init_env(char **envp)
{
	int		iter;
	t_pair	*env_var;
	t_env	env;

	env.nb_vars = -1;
	while(envp[++env.nb_vars])
		;
	env.array = xmalloc(sizeof(char *) * (env.nb_vars + 1), __FILE__, __LINE__);
	env.list = NULL;
	iter = -1;
	while(envp[++iter])
	{	
		env_var = build_var_pair(envp[iter]);
		ft_lstadd_back(&env.list, ft_lstnew(env_var));
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

bool	is_env_var(t_env *env, char *key)
{
	t_list	*tmp;

	tmp = env->list;
	while (tmp)
	{
		if (!ft_strncmp(((t_pair *)tmp->content)->key, key, ft_strlen(key) + 1))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	update_env_var(char *key, char *new_value)
{
	t_list	*tmp;
	int		iter;
	t_env	*env;

	env = &get_data(NULL)->env;
	tmp = env->list;
	iter = -1;
	while(++iter < env->nb_vars)
	{
		if ((!ft_strncmp(((t_pair *)tmp->content)->key, key, ft_strlen(key) + 1)))
		{
			free(env->array[iter]);
			env->array[iter] = ft_strnjoin(3, key, "=", new_value);
			free(((t_pair *)tmp->content)->value);
			((t_pair *)tmp->content)->value = ft_strdup(new_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	print_env_vars(t_list *env, int *ctx)
{
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", ctx[1]);
		ft_putstr_fd(((t_pair *)tmp->content)->key, ctx[1]);
		if(((t_pair *)tmp->content)->value)
		{
			ft_putstr_fd("=", ctx[1]);
			ft_putstr_fd(((t_pair *)tmp->content)->value, ctx[1]);
		}
		write(ctx[1], "\n", 1);
		tmp = tmp->next;
	}
}

char	*get_env_var(char *key)
{
	t_list	*tmp;


	tmp = get_data(NULL)->env.list;
	while(tmp)
	{
		if(!ft_strncmp(((t_pair *)tmp->content)->key, key, ft_strlen(key) + 1))
			return (((t_pair *)tmp->content)->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	__export(char **args, int *ctx)
{
	t_pair	*pair;
	t_data	*data;

	data = get_data(NULL);
	if (!args[1])
	{
		print_env_vars(data->env.list, ctx);
		return (0);
	}
	pair = build_var_pair(args[1]);
	if (is_env_var(&data->env, pair->key))
		update_env_var(pair->key, pair->value);
	else
	{
		ft_lstadd_back(&data->env.list, ft_lstnew(pair));
		data->env.array = ft_push_to_matrix(data->env.array, args[1]);
	}
	return (0);
}

int	__env(char **args, int *ctx)
{
	t_list	*tmp;

	(void)args;
	tmp = get_data(NULL)->env.list;
	while (tmp)
	{	
		if(((t_pair *)tmp->content)->value)
		{
			ft_putstr_fd(((t_pair *)tmp->content)->key, ctx[1]);
			ft_putstr_fd("=", ctx[1]);
			ft_putstr_fd(((t_pair *)tmp->content)->value, ctx[1]);
			write(ctx[1], "\n", 1);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	__unset(char **args, int *ctx)
{
	(void)args;
	(void)ctx;
	return (0);
}
