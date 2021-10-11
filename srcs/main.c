#include "../headers/main.h"

int main(int argc, char **argv)
{
	t_data	data;

	init_data(&data, argc, argv);
	while (!data.exit_cmd)
	{
		data.input = readline(PROMPT);
		parse_input(&data);
		execute_input(&data);
		//free_data_cmd;
		free(data.input);
		data.input = NULL;
	}
	free_data(&data);
	return (0);
}

