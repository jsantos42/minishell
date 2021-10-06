#include "../headers/main.h"

static void	init_data(t_data *data, int argc, char **argv);

int main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	while (true)
	{
		data.input = readline(PROMPT);
		parse_input(&data);
		free(data.input);
		data.input = NULL;
	}
	if (data.paths)
		ft_free_matrix((void**)data.paths, data.nb_paths);
	return (0);
}

static void	init_data(t_data *data, int argc, char **argv)
{
	char	*env_paths;

	if (argc > 1)
		exit (0);
	(void)argv;
	data->paths = NULL;
	data->input = NULL;
	env_paths = getenv("PATH");
	if (!env_paths)
		handle_error(ENV_VAR);
	data->paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!data->paths)
		handle_error(MALLOC);
}


//// TESTS, ERASE THIS
//char *location;
//location = getcwd(NULL, 0);
//printf("%s\n", location);
//int iter = -1;
//while (data.paths[++iter] != NULL)
//printf("%s\n", data.paths[iter]);
