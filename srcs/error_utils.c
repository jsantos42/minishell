#include "../headers/error_utils.h"

void	handle_error(int error)
{
//	free_data;
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
