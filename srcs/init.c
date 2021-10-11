#include "../headers/init.h"

void	init_data(t_data *data, int argc, char **argv)
{
	char	*env_paths;

	if (argc > 1)
		exit (0);
	(void)argv;
	data->paths = NULL;
	data->input = NULL;
	data->exit_cmd = false;
	data->commands = NULL;
	env_paths = getenv("PATH");
	if (!env_paths)
		terminate_program(ENV_VAR, data);
	data->paths = ft_split(env_paths, ':', &data->nb_paths);
	if (!data->paths)
		terminate_program(MALLOC, data);
}

void	init_command(t_data *data, t_cmd **command)
{
	*command = NULL;
	if (!ft_other_malloc((void**)command))
		terminate_program(MALLOC, data);
	(*command)->cmd = NULL;
	(*command)->redir_input = NULL;
	(*command)->redir_output = NULL;
	(*command)->args = NULL;
	(*command)->args = NULL;
	(*command)->nb_args = 0;
	(*command)->relation_to_next = 0;
	(*command)->next = NULL;
}
