#include "../headers/init.h"

static char	**get_paths(t_data *data);
static t_list *ft_init_env(char **envp);

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	if (argc > 1)
		exit(0);
	(void) argv;
	data->envp = envp;
	data->input = NULL;
//	data->paths = NULL;
	data->nb_paths = 0;
	data->status = 0;
	data->paths = get_paths(data);
	data->tree = NULL;
	data->exit_cmd = false;
	data->plist = NULL;
	data->env = ft_init_env(envp);
	get_data(data);
}

t_tree	*init_leaf_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program(MALLOC);
	new_node->type = LEAF_NODE;
	new_node->leaf.args = NULL;
	new_node->leaf.nb_args = 0;
	new_node->leaf.redir_input = NULL;
	new_node->leaf.redir_output = NULL;
	new_node->leaf.append_mode = false;
	new_node->leaf.here_doc = false;
	new_node->leaf.delimiter = NULL;
	new_node->previous = previous;
	return (new_node);
}

t_tree	*init_branch_node(t_tree *previous)
{
	t_tree	*new_node;

	new_node = NULL;
	new_node = malloc(sizeof(t_tree));
	if (!new_node)
		terminate_program(MALLOC);
	new_node->type = BRANCH_NODE;
	new_node->branch.operator = 0;
	new_node->branch.left = NULL;
	new_node->branch.right = NULL;
	new_node->previous = previous;
	return (new_node);
}

static char	**get_paths(t_data *data)
{
	char	*env_paths;
	char	**paths;

	env_paths = getenv("PATH");
	if (!env_paths)
		terminate_program(ENV_VAR);
	paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!paths)
		terminate_program(MALLOC);
	return (paths);
}

static t_list *ft_init_env(char **envp)
{
	int		iter;
	int		tmp;
	t_list	*env_list;
	char	**line;
	t_pair	*pair;

	env_list = NULL;
	iter = -1;
	while(envp[++iter])
	{	pair = malloc(sizeof(t_pair));
		if (!pair)
			terminate_program(MALLOC);
		line = ft_split(envp[iter], '=', &tmp);
		pair->key = ft_strdup(line[0]);
		pair->value = ft_strdup(line[1]);
		ft_lstadd_back(&env_list, ft_lstnew(pair));
		free(line[0]);
		free(line[1]);
		free(line);
	}
	return (env_list);
}
