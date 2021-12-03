#ifndef MAIN_H
# define MAIN_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include "../libs/libft/include/libft.h" // this already includes stdlib.h and unistd.h
# include "types.h"
# include "ansi_colors.h" // Color Macros
# include "builtins.h"
# include "dollar_sign.h"
# include "env.h"
# include "escape_char.h"
# include "execute_input.h"
# include "heredoc.h"
# include "init.h"
# include "parse_input.h"
# include "parse_input_utils.h"
# include "redirect_input.h"
# include "redirect_output.h"
# include "quote_char.h"
# include "semicomma.h"
# include "special_chars.h"
# include "special_chars_utils.h"
# include "terminate_and_free.h"

t_data	*get_data(t_data *data);

char	*ft_strnjoin(int count,...);

void	*xmalloc(size_t size, char *file, int line);

char	**ft_push_to_matrix(char **array, char *str);

#endif