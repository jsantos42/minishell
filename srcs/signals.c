#include "../headers/signals.h"

/*
**	Hijacks the default response to the SIGINT and SIGQUIT signals. According to
**	the subject:
**	 - ctrl-C should print a new prompt on a newline.
**	 - ctrl-D should exit the shell.
**	 - ctrl-\ should do nothing.
*/

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*
**	These next two functions work together. When the program receives a SIGINT,
**	sigint_handler is called and closes the STDIN file descriptor and switch the
**	sigint_received flag. Before closing the STDIN it stores a copy on data.
**	On the other hand when the sigint_received flag is on, the main function
**	calls get_new_prompt_line to recover the STDIN fd to the origin and turning
**	off the flag.
*/

void	sigint_handler(int signal)
{
	t_data	*data;

	(void)signal;
	data = get_data(NULL);
	data->stdin_fd = dup(STDIN_FILENO);
	data->sigint_received = true;
	close(STDIN_FILENO);
}

void	get_new_prompt_line(t_data *data)
{
	dup2(data->stdin_fd, STDIN_FILENO);
	write(STDIN_FILENO, "\n", 1);
	data->sigint_received = false;
	close(data->stdin_fd);
}
