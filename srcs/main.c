#include "../headers/main.h"

char	**get_paths(char **env);

int main(int argc, char **argv, char **env)
{
	char	**paths;

	(void)argc;
	(void)argv;
	paths = get_paths(env);
//	int iter = -1;
//	while (paths[++iter] != NULL)
//		printf("%s\n", paths[iter]);
	return 0;
}


char	**get_paths(char **env)
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
	paths = ft_split(paths_str, ':');
	if (!paths)
		handle_error(FAILED_MALLOC);
	return (paths);
}
