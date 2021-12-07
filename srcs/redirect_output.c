#include "../headers/redirect_output.h"

void	handle_output_redirection(t_tree **current_node, t_data *data, int *i)
{
	int	old_i;

	(*i)++;
	if (data->input[*i] == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*i)++;
	}
	skip_white_space(data->input, i);
	old_i = *i;
	while (data->input[*i] != '\0'
		   && !is_special_char(data->input[*i])
		   && !ft_isspace((data->input)[*i]))
	{
		if (is_quote_char((data->input)[*i]))
			handle_quote_char(data, i);
		else if (is_dollar_sign((data->input)[*i]))
			handle_dollar_sign(data, i);
		(*i)++;
	}
	if (*i != old_i)
		(*current_node)->leaf.redir_output = ft_substr(data->input, old_i, *i - old_i);
}
