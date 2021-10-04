#include "../headers/main.h"

char	**get_paths(char **env, int *nb_paths);

int main(int argc, char **argv, char **env)
{
	char	**paths;
	int		nb_paths;

	(void)argc;
	(void)argv;
	paths = get_paths(env, &nb_paths);
//	int iter = -1;
//	while (paths[++iter] != NULL)
//		printf("%s\n", paths[iter]);
	if (paths)
		ft_free_matrix((void**)paths, nb_paths);
	return 0;
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
