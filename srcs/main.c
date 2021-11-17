#include "../headers/main.h"

int main(int argc, char **argv, char **envp)
{
	t_data	data;

	init_data(&data, argc, argv, envp);
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

t_data	*get_data(t_data *data)
{
	static t_data *static_data = NULL;

	if (!static_data && data)
		static_data = data;
	return (static_data);
}