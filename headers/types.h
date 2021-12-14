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

/*
**	Enum that stores the errors that the program can throw.
*/

typedef enum e_errors {
	MALLOC			= -1,
	DUP2			= -2,
	CMD_NOT_FOUND	= -3
}	t_errors;

/*
**	Enum that stores the builtins.
*/

typedef enum e_builtins {
	__ECHO,
	__CD,
	__PWD,
	__EXPORT,
	__UNSET,
	__ENV,
	__EXIT
}	t_builtins;

/*
**	Struct that has the environment variables, both in a list and in an array.
*/

typedef struct s_env
{
	int		nb_vars;
	t_list	**list;
	char	**envp;
	char	**array;
}	t_env;

typedef struct s_pair
{
	char	*key;
	char	*value;
}	t_pair;

/*
**	Enum that stores the operator between commands in the Abstract Syntax
**	Tree; note that this was implemented in order to deal with AND and OR
**	operators, but due to time constraints we ended up not doing it.
*/

typedef enum e_operator {
	PIPE	= 1,
	OR		= 2,
	AND		= 3
}	t_operator;

/*
**	The Abstract Syntax Tree has 2 kinds of nodes:
**	 - the leaf one (which is essentially a dead end); and
**	 - the branch one (which is essentially a fork).
*/

typedef enum e_node_type {
	LEAF_NODE	= 1,
	BRANCH_NODE	= 2
}	t_node_type;

/*
**	The branch node stores a pointer to a left node (which will always be of
**	leaf type) and to a right node. It also stores the operator between them.
*/

typedef struct s_branch_node
{
	struct s_tree	*left;
	struct s_tree	*right;
	int				operator;
}	t_branch_node;

/*
**	The leaf node stores:
**	 - a matrix of arguments (the first of which should be the command)
**	 - the number of args, required to manage memory (de)allocation; note that
**	 since the first arg is the command itself, if the command has no arguments
**	 the nb_args will be 1 (and not 0)
**	 - the name of the file from which to read input (if given)
**	 - the name of the file to which to write output (if given)
**	 - a flag that identifies when in heredoc_mode
**	 - the file where to store the heredoc input
**	 - the delimiter to end the heredoc mode
*/

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

/*
**	Each node from the Abstract Syntax Tree has a type, the node in itself
**	(which could be of type branch or leaf) and a pointer to the previous node.
*/

typedef struct s_tree {
	t_node_type		type;
	union {
		t_branch_node	branch;
		t_leaf_node		leaf;
	};
	struct s_tree	*previous;
}	t_tree;

/*
**	This is the main structure of the program. It stores:
**	 - the user input
**	 - the Abstract Syntax Tree
**	 - a flag that informs whether the input is illegal
**	 - a flag that informs whether the char to be parsed is escaped
**	 - a flag that informs whether a SIGINT was received
**	 - an integer to store a copy of the STD_INPUT
**	 - the environment of the program
**	 - the exit status of the last command
**	 - a list of the running processes
*/

typedef struct s_data {
	char	*input;
	t_tree	*tree;
	bool	forbidden_chars;
	bool	escaped;
	bool	sigint_received;
	int		stdin_fd;
	t_env	env;
	int		status;
	t_list	*plist;
}	t_data;

#endif
