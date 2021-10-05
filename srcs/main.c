#include "../headers/main.h"

char	**get_paths(char **env, int *nb_paths);
void	handle_input(char *input, char **paths, bool *exit_flag);

int main(int argc, char **argv, char **env)
{
	char	**paths;
	int		nb_paths;
	char	*input;
	bool	exit_flag;

	(void)argc;
	(void)argv;
	paths = get_paths(env, &nb_paths);
	exit_flag = false;
	while (!exit_flag)
	{
		input = readline("minishell-1.0$ ");
		handle_input(input, paths, &exit_flag);
		free(input);
	}
	if (paths)
		ft_free_matrix((void**)paths, nb_paths);
	return (0);
}


void	handle_input(char *input, char **paths, bool *exit_flag)
{
	if (!ft_strncmp(input, "exit", 5))
	{
		printf("%s\n", input);
		*exit_flag = true;
	}
//	else
//		look for command in paths
	(void)paths;

}

char	**get_paths(char **env, int *nb_paths)
{
	char	*paths_str;
	char	**paths;
	int		iter;

	paths_str = NULL;
	iter = -1;
	while (env[++iter] != NULL)
	{
		if (!ft_strncmp(env[iter], "PATH=", 5))
		{
			paths_str = env[iter] + 5;
			break ;
		}
	}
	paths = ft_split(paths_str, ':', nb_paths);
	if (!paths)
		handle_error(FAILED_MALLOC);
	return (paths);
}
