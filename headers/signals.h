#ifndef SIGNALS_H
# define SIGNALS_H

# include "main.h"

void	init_signals(void);
void	sigint_handler(int signal);
void	get_new_prompt_line(t_data *data);

#endif
