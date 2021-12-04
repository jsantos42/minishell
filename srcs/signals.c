#include "../headers/signals.h"

void	handle_signals(int signal)
{
	t_data	*data;

	data = get_data(NULL);
	if (signal == SIGINT)
	{
		data->stdin_fd = dup(STDIN_FILENO);
		data->sigint_received = true;
		close(STDIN_FILENO);
	}
//		ctrl-Cprint a new prompt on a newline.
//		◦ctrl-Dexit the shell.
//		◦ctrl-\do nothing.

}



/*
** The main function could act like server in minishell.
 * The execution process is a fork itself, and when its forked, it sends its pid
 * to the main process (save it in t_data).
** Everytime a new process is forked (execution of it), it sends a signal to the
 * execution process, informing it of its existence and passing pid to info->si_pid.
** Everytime those forked processes end, they also inform the execution process
 * that they are quitting.
** Main only knows whether the execution process is running, and when it gets a
 * signal it can interrupt it.
 * The execution process keeps a record of the pids that needs to kill in case
 * it receives a signal from main. If the execution process is running, it then
 * prints ^C (in case of SIGINT).
 * attention to segfault when ctrD
*/