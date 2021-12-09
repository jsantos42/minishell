#include "../headers/main.h"

static void	check_for_arguments(int argc, char **argv);
/*
**	1) Checks for arguments, which are not expected by the program.
**	2) Initiates the data structure.
**	3) Sets the program to read the history from a given file.
**	4) Gets into an infinite loop, during which it will receive input from the
**	user, add it to the history, parse it and execute it. This normal behaviour
**	doesn't take place if:
**		- the sigint_received flag is on, meaning the program has received a
**		SIGINT signal; if so, it calls get_new_prompt_line.
**		- the input is NULL, meaning the program has received an EOF (Ctrl-D);
**		if so, it calls the built-in exit command to end the program.
**		- the input is an empty string; if so, frees the input and asks the user
**		for a new one.
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	check_for_arguments(argc, argv);
	init_data(&data, envp);
	init_history();
	while (1)
	{
		data.input = readline(PROMPT);
		if (data.sigint_received)
			get_new_prompt_line(&data);
		else if (!data.input)
			__exit(NULL, NULL);
		else if (ft_strncmp(data.input, "", NULLTERM) != 0)
		{
			add_history(data.input);
			parse_input(&data);
			execute_input(&data);
			write_history(".history");
		}
		data.input = free_if_not_null(data.input);
	}
}

/*
**	This shell does not have a non-interactive mode, so if it receives arguments
**	it exits.
*/

static void	check_for_arguments(int argc, char **argv)
{
	(void)argv;
	if (argc > 1)
	{
		printf("Minishell does not require arguments. Please try again.\n");
		exit(0);
	}
}

/*
**	This is a singleton to get the data variable available everywhere in the
**	code at the call of a function, avoiding the need to pass data as an
**	argument for every function.
*/

t_data	*get_data(t_data *data)
{
	static t_data	*static_data = NULL;

	if (!static_data)
		static_data = data;
	return (static_data);
}
