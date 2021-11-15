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

typedef struct s_branch_node {
	int				operator;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_branch_node;

typedef struct s_leaf_node {
	char			*cmd;
	char			**args;
	int				nb_args; //necessary to know how much memory to allocate
	char			*redir_input;
	char			*redir_output;
	bool			append_mode;
	bool			here_doc;
	char 			*delimiter;
}	t_leaf_node;

typedef struct s_tree {
	union {
		t_branch_node	branch;
		t_leaf_node		leaf;
	};
	struct s_tree	*previous;
}	t_tree;

typedef struct s_data {
	char	*input;
	char	**paths;
	int		nb_paths;
	t_tree	*tree;
	bool	exit_cmd;
	bool	illegal_input;
}	t_data;

#endif