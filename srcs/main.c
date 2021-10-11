#include "../headers/main.h"

int main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	while (!data.exit_cmd)
	{
		data.input = readline(PROMPT);
		if (parse_input(&data))
			execute_input(&data);
		free_commands(data.commands);
		free_if_not_null(data.input);
		data.input = NULL;
	}
	free_data(&data);
	return (0);
}

