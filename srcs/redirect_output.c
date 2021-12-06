#include "../headers/redirect_output.h"

void	handle_output_redirection(t_tree **current_node, char **str, int *i)
{
	int	old_i;

	(*i)++;
	if ((*str)[*i] == '>')
	{
		(*current_node)->leaf.append_mode = true;
		(*i)++;
	}
	skip_white_space(*str, i);
	old_i = *i;
	while ((*str)[*i] != '\0'
		   && !is_special_char((*str)[*i])
		   && !ft_isspace((*str)[*i]))
	{
		if (is_quote_char((*str)[*i]))
			*str = handle_quote_char(*str, i);
		else if (is_dollar_sign((*str)[*i]))
			*str = handle_dollar_sign(*str, *i);
		(*i)++;
	}
	if (*i != old_i)
		(*current_node)->leaf.redir_output = ft_substr(*str, old_i, *i - old_i);
}
