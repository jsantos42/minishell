#include "../headers/main.h"

char	**get_paths(int *nb_paths);
void	handle_input(char *input, char **paths, bool *exit_flag);
int	is_a_valid_command(char *input, char **paths);
int	is_in_dir(char *input, DIR *directory);

int main(int argc, char **argv)
{
	char	**paths;
	int		nb_paths;
	char	*input;
	bool	exit_flag;

	(void)argv;
	if (argc > 1)
		return (0);
	paths = get_paths(&nb_paths);
	exit_flag = false;
	while (!exit_flag)
	{
		input = readline("minishell-1.0$ ");
		handle_input(input, paths, &exit_flag);
		free(input);
	}

				// TESTS, ERASE THIS
				char *location;
				location = getcwd(NULL, 0);
				printf("%s\n", location);
				int iter = -1;
				while (paths[++iter] != NULL)
					printf("%s\n", paths[iter]);

	if (paths)
		ft_free_matrix((void**)paths, nb_paths);
	return (0);
}


char	**get_paths(int *nb_paths)
{
	char	*paths_str;
	char	**paths;

	paths_str = getenv("PATH");
//	if (!paths)
//		handle_error(NOT_ENV_VAR);
	paths = ft_split(paths_str, ':', nb_paths);
	if (!paths)
		handle_error(FAILED_MALLOC);
	return (paths);
}

void	handle_input(char *input, char **paths, bool *exit_flag)
{
	if (!ft_strncmp(input, "exit", 5))
	{
		printf("%s\n", input);
		*exit_flag = true;
	}
	else if (is_a_valid_command(input, paths))
		printf("%s is a command!\n", input);
	else
		printf("%s is NOT a command!\n", input);
}

int	is_a_valid_command(char *input, char **paths)
{
	DIR	*directory;
	int	iter;


	iter = -1;
	while (paths[++iter] != NULL)
	{
		directory = opendir(paths[iter]);
		if (is_in_dir(input, directory))
			return (1);
	}
	return (0);
}

int	is_in_dir(char *input, DIR *directory)
{
	struct dirent *dir_struct;

	while (1)
	{
		dir_struct = readdir(directory);
		if (dir_struct != NULL)
		{
			if (ft_strncmp(input, dir_struct->d_name, ft_strlen(input) + 1) == 0)
				return (1);
		}
		else
		{
//			check_errno //to see if error;
//			if (closedir(directory) != 0)
//				handle_error(CLOSING_FILE);
			return (0);
		}
	}


}