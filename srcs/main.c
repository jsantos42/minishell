#include "../headers/main.h"

static void	get_paths(t_data *data);

int main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	get_paths(&data);
	while (!data.exit_cmd)
	{
		data.input = readline(PROMPT);
		if (parse_input(&data))
			execute_input(&data);
//		free_commands(data.commands);
		free_if_not_null(data.input);
		data.input = NULL;
	}
	free_data();
	return (0);
}

static void	get_paths(t_data *data)
{
	char *env_paths;

	env_paths = getenv("PATH");
	if (!env_paths)
		terminate_program(ENV_VAR);
	data->paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!data->paths)
		terminate_program(MALLOC);
}

t_data	*get_data(t_data *data)
{
	static t_data *static_data = NULL;

	if (!static_data && data)
		static_data = data;
	return (static_data);
}


/// change args to first arg as command and null terminated

