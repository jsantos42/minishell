#ifndef TYPES_H
# define TYPES_H

# include "main.h"

# define PROMPT "minishell-1.0$ "
typedef enum e_errors {
	MALLOC			= -1,
	ENV_VAR			= -2,
	OPENING_DIR		= -4,
	READING_DIR		= -5,
	CLOSING_DIR		= -6
}	t_errors;


typedef struct	s_data {
	char	**paths;
	int		nb_paths;
	char	*input;
}	t_data;

#endif