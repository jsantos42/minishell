#ifndef TYPES_H
# define TYPES_H

# include "main.h"

# define PROMPT "minishell-1.0$ "


typedef enum e_errors {
	MALLOC			= -1,
	ENV_VAR			= -2,
	OPENING_DIR		= -4,
	READING_DIR		= -5,
	CLOSING_DIR		= -6,
	SPECIAL_CHAR	= -7,
	UNCLOSED_QUOTES	= -8,
	RUN_BG			= -9
}	t_errors;

typedef enum e_relation {
	PIPE	= 1,
	OR		= 2,
	AND		= 3
}	t_relation;

typedef struct	s_cmd {
	char			*cmd;
	char			*redir_input;
	char			*redir_output;
	char			**args;
	int				nb_args;
	int				relation_to_next;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_data {
	char	*input;
	char	**paths;
	int		nb_paths;
	t_cmd	*commands;
	bool	exit_cmd;
}	t_data;

#endif