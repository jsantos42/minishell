#include "../headers/main.h"

static void	check_for_arguments(int argc, char **argv);
/*
 *	1) Checks for arguments, which are not expected by the program.
**	2) Initiates the data structure.
**	3) Sets the program to read the history from a given file.
**	4) If the sigint_received flag is on, it means the program has received a
**	SIGINT signal, and calls get_new_prompt_line.
**	5) If the input is NULL, it means the program received an EOF (Ctrl-D), and
**	it calls the built-in exit command to end the program.
**	6) In case the input is not an empty string, it parses and executes it.
*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	check_for_arguments(argc, argv);
	init_data(&data, envp);
	read_history(".history");
	while (1)
	{
		data.input = readline("\033[38;5;214m𓆉  Minishell $ ");
		add_history(data.input);
		if (data.sigint_received)
			get_new_prompt_line(&data);
		else if (!data.input)
			builtin_exit();
		else if (ft_strncmp(data.input, "", 1) != 0)
		{
			parse_input(&data);
			execute_input(&data);
		}
		data.input = free_if_not_null(data.input);
	}
}

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
