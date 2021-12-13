/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:48:15 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 20:39:36 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "main.h"

typedef enum e_errors {
	MALLOC			= -1,
	ENV_VAR			= -2,
	OPENING_DIR		= -4,
	READING_DIR		= -5,
	CLOSING_DIR		= -6,
	SPECIAL_CHAR	= -7,
	UNCLOSED_QUOTES	= -8,
	RUN_BG			= -9,
	DUP2			= -10,
	CMD_NOT_FOUND	= -11
}	t_errors;

typedef enum e_builtins {
	__ECHO,
	__CD,
	__PWD,
	__EXPORT,
	__UNSET,
	__ENV,
	__EXIT
}	t_builtins;

typedef enum e_relation {
	PIPE	= 1,
	OR		= 2,
	AND		= 3
}	t_relation;

typedef struct s_env
{
	int		nb_vars;
	t_list	**list;
	char	**envp;
	char	**array;
}	t_env;

typedef enum e_node_type {
	LEAF_NODE	= 1,
	BRANCH_NODE	= 2
}	t_node_type;

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

typedef struct s_branch_node
{
	int				operator;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_branch_node;

typedef struct s_leaf_node {
	char			**args;
	int				nb_args;
	char			*redir_input;
	char			*redir_output;
	bool			append_mode;
	bool			here_doc;
	char			*heredoc_file;
	char			*delimiter;
}	t_leaf_node;

typedef struct s_tree {
	t_node_type		type;
	union {
		t_branch_node	branch;
		t_leaf_node		leaf;
	};
	int				redir_io[2];
	struct s_tree	*previous;
}	t_tree;

typedef struct s_data {
	char	*input;
	t_env	env;
	int		nb_paths;
	int		status;
	bool	forbidden_chars;
	t_tree	*tree;
	int		stdin_fd;
	bool	sigint_received;
	bool	escaped;
	t_list	*plist;
}	t_data;

#endif
