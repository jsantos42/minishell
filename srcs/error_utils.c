#include "../headers/error_utils.h"

void	handle_error(int error)
{
	printf("Error\n");
	if (error == FAILED_MALLOC)
		printf("Memory allocation failed.\n");
	exit(error);
}
