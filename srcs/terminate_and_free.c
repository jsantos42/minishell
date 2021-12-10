#include "../headers/terminate_and_free.h"

void	terminate_program(char *name, int error)
{
	free_data();
	printf("ERROR\n");
	if (error == MALLOC)
		printf("Memory allocation failed.\n");
	else if (error == DUP2)
		printf("%s: Error copying file descriptors\n", name);
	else if (error == CMD_NOT_FOUND)
		printf("%s: command not found\n", name);
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
