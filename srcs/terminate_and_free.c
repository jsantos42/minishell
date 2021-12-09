#include "../headers/terminate_and_free.h"

void	terminate_program(int error)
{
	free_data();
	printf("ERROR\n");
	if (error == MALLOC)
		printf("Memory allocation failed.\n");
	else if (error == ENV_VAR)
		printf("There's no such variable in the current environment.\n");
	else if (error == OPENING_DIR)
		printf("Could not open a directory.\n");
	else if (error == READING_DIR)
		printf("Could not read a directory.\n");
	else if (error == CLOSING_DIR)
		printf("Could not close a directory.\n");
	exit(error);
}

void	free_data(void)
{
	t_data	*data;

	data = get_data(NULL);
//	free_if_not_null(data->input);
//	free_matrix((void **) data->paths, data->nb_paths);
//	free_commands(data->commands);
}
