#include "../headers/main.h"

static void	init_data(t_data *data, int argc, char **argv);

int main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	while (!data.exit_cmd)
	{
		data.input = readline(PROMPT);
		parse_input(&data);
		execute_input(&data);
		free(data.input);
		data.input = NULL;
	}
	free_data(&data);
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
	data->cmd = NULL;
	data->exit_cmd = false;
	env_paths = getenv("PATH");
	if (!env_paths)
		terminate_program(ENV_VAR, data);
	data->paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!data->paths)
		terminate_program(MALLOC, data);
}
