/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:25 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:19 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include "../libs/libft/include/libft.h" // this already includes stdlib.h and unistd.h
# include "types.h"
# include "ansi_colors.h" // Color Macros
# include "built-ins/builtins.h"
# include "parser/dollar_sign.h"
# include "env/env.h"
# include "parser/escape_char.h"
# include "executor/execute_input.h"
# include "executor/heredoc.h"
# include "init.h"
# include "libft_extra.h"
# include "parser/parse_input.h"
# include "parser/parse_input_utils.h"
# include "parser/redirect_input.h"
# include "parser/redirect_output.h"
# include "parser/quote_char.h"
# include "parser/semicomma.h"
# include "signals.h"
# include "parser/special_chars.h"
# include "parser/special_chars_utils.h"
# include "terminate_and_free.h"

# define PROMPT "\033[38;5;214m𓆉  Minishell $ "

t_data	*get_data(t_data *data);
void	check_for_arguments(int argc, char **argv);

#endif
