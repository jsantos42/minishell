#include "../headers/error_utils.h"

void	handle_error(int error)
{
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
