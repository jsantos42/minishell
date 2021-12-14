/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:46:25 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 19:59:00 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include "../libs/libft/include/libft.h"
# include "types.h"
# include "ansi_colors.h"
# include "built-ins/builtins.h"
# include "env/env.h"
# include "env/env_accessors.h"
# include "executor/execute_input.h"
# include "executor/exec_utils.h"
# include "executor/heredoc.h"
# include "init.h"
# include "libft_extra.h"
# include "parser/dollar_sign.h"
# include "parser/escape_char.h"
# include "parser/parse_input.h"
# include "parser/parse_input_utils.h"
# include "parser/quote_char.h"
# include "parser/redirect_input.h"
# include "parser/redirect_output.h"
# include "parser/semicomma.h"
# include "parser/special_chars.h"
# include "parser/special_chars_utils.h"
# include "signals.h"
# include "error_utils.h"

# define PROMPT "\033[38;5;214m𓆉  Minishell $ "

t_data	*get_data(t_data *data);
void	check_for_arguments(int argc, char **argv);

#endif
