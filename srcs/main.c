#include "../headers/main.h"

static char *prompt[] = {
	"\n\033[38;5;214m𓆉  Minishell $ ",
	"\n\033[38;5;196m𓆉  Minishell $ ",
	"\n\033[38;5;93m𓆉  Minishell $ ",
	"\n\033[38;5;39m𓆉  Minishell $ "
	};
int main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i = 0;

	init_data(&data, argc, argv, envp);
	while (!data.exit_cmd)
	{
		data.input = readline(prompt[i]);
		if (parse_input(&data))
			execute_input(&data);
//		free_commands(data.commands);
		free_if_not_null(data.input);
		data.input = NULL;
		i = i != 3 ? i + 1 : 0;
	}
	free_data();
	return (0);
}

t_data	*get_data(t_data *data)
{
	static t_data *static_data = NULL;

	if (!static_data && data)
		static_data = data;
	return (static_data);
}
