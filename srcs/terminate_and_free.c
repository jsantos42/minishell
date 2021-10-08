#include "../headers/terminate_and_free.h"

void	terminate_program(int error, t_data *data)
{
	free_data(data);
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
	else if (error == SPECIAL_CHAR)
	{
		printf("Minishell should not interpret unspecified special characters");
		printf(" like '\\' or ';'.\n");
	}
	else if (error == UNCLOSED_QUOTES)
		printf("Minishell should not interpret unclosed quotes.\n");
	exit(error);
}

void	free_data(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->paths)
		ft_free_matrix((void**)data->paths, data->nb_paths);
	if (data->commands)
		ft_free_matrix((void**)data->commands, data->nb_commands);
}