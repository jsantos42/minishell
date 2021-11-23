#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <string.h>
# include <sys/errno.h>
# include "ansi_colors.h" // Color Macros
# include "../libs/libft/include/libft.h" // this already includes stdlib.h and unistd.h
# include "types.h"
# include "terminate_and_free.h"
# include "init.h"
# include "parse_input.h"
# include "parse_input_utils.h"
# include "execute_input.h"
# include "special_chars.h"
# include "special_chars_utils.h"
# include "dollar_sign.h"
# include "quote_char.h"

t_data	*get_data(t_data *data);

#endif