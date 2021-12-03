#include "../headers/builtins.h"

void	builtin_echo(char **args, int *ctx)
{
	int		iter;
	bool	new_line;
	bool	print_space;
	
	iter = 1;
	if (args[iter] && !ft_strncmp(args[iter], "-n", 3))
	{
		new_line = false;
		iter = 2;
	}
	else
		new_line = true;
	print_space = false;
	while (args[iter])
	{
		if (print_space)
			write(ctx[1], " ", 1);
		else
			print_space = true;
		write(ctx[1], args[iter], ft_strlen(args[iter]));
		iter++;
	}
	if (new_line)
		write(ctx[1], "\n", 1);
}

// static char *ft_get_prev_dir(char *path);

void	builtin_cd(char **args)
{
	char	*cur_dir;
	char	*path;

	cur_dir = getcwd(NULL, 0);

	if (!ft_strncmp(args[1], "./", 2) || !ft_strncmp(args[1], "../", 3))
		path = ft_ultra_strjoin(3, cur_dir, "/", args[1]);
	else
		path = args[1];
	if(chdir(path) == -1)
		printf("Error changing directory\n");
}

// static char *ft_get_prev_dir(char *path)
// {
// 	int		len;
// 	char	*prev_dir;

// 	len = ft_strlen(path);
// 	while(path[len] != '/')
// 		len--;
// 	prev_dir = ft_substr(path, 0, len);
// 	return (prev_dir);
// }

void	builtin_env(int *ctx)
{
	t_list	*tmp;

	tmp = get_data(NULL)->env;
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
}

void	builtin_export(t_data *data, char **args, int *ctx)
{
	t_pair	*pair;
	char	**var;
	int		splt_c;
	t_list	*tmp;

	if (!args[1])
		print_env_vars(data->env, ctx);
	else
	{
		pair = malloc(sizeof(t_pair));
		if (args[1] != NULL && !ft_strchr(args[1], '='))
		{
			pair->key = ft_strdup(args[1]);
			pair->value = NULL;
		}
		else
		{
			var = ft_split(args[1], '=', &splt_c);
			pair->key = ft_strdup(var[0]);
			pair->value = ft_strdup(var[1]);
			free(var[0]);
			free(var[1]);
			free(var);
			tmp = data->env;
			while(tmp)
			{
				if(!ft_strncmp(((t_pair *)tmp->content)->key, pair->key, ft_strlen(pair->key)))
				{
					free(((t_pair *)tmp->content)->value);
					((t_pair *)tmp->content)->value = pair->value;
					free(pair->key);
					return ;
				}
				tmp = tmp->next;
			}
		}
		ft_lstadd_back(&data->env, ft_lstnew(pair));
	}
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

void	builtin_exit(void)
{
	write_history(".history");
	exit(EXIT_SUCCESS);
}
