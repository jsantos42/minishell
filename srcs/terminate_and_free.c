#include "../headers/terminate_and_free.h"

void	terminate_program(char *name, int error)
{
	free_data();
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
	else if (error == RUN_BG)
		printf("Minishell should not deal with job control. Did you mean '&&'?\n");
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

//void	free_commands(t_cmd *commands)
//{
//	t_cmd *temp;
//
//	while (commands)
//	{
//		temp = commands->next;
//		free_if_not_null(commands->cmd);
//		free_if_not_null(commands->redir_input);
//		free_if_not_null(commands->redir_output);
//		free_matrix((void **) commands->args, commands->nb_args);
//		commands = temp;
//	}
//}
