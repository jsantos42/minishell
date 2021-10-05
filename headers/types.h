#ifndef TYPES_H
# define TYPES_H

# include "main.h"

typedef enum e_errors {
	MALLOC			= -1,
	ENV_VAR			= -2,
	OPENING_DIR		= -4,
	READING_DIR		= -5,
	CLOSING_DIR		= -6
}	t_errors;

#endif