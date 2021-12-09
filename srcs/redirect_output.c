#include "../headers/redirect_output.h"

void	handle_output_redirection(t_tree **current_node, t_data *data, int *i)
{
	char	*redir;

	(*i)++;
	if (data->input[*i] == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*i)++;
	}
	skip_white_space(data->input, i);
	redir = parser_core(data, i);
	if (redir)
		(*current_node)->leaf.redir_output = redir;
}
