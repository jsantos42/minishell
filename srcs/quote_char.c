#include "../headers/quote_char.h"

bool	is_quote_char(char chr)
{
	return (chr == '\'' || chr == '\"');
}

/*
**	This makes sure nothing between quotes gets interpreted as a command.
**	1) It starts by defining which type of quote it's using.
**	2) Creates a new_input string, which will be a copy of input without the
**	pair of quotes it's handling.
**	3) Parses through the input string and copies it to new_input, except for
**	the quote_type char (unless it's escaped). Continues to do so until it finds
**	a closing quote.
**	4) If it found a closing quote, saves the new position (that will be passed
**	to scanner->cursor) and copies the rest of the input string to new_input,
**	NULL-terminating it and returning it.
**	NOTE: when saving the new quote_pos, it uses j (instead of i) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

void	handle_quote_char(t_data *data, int *quote_pos)
{
	char	quote_type;
	char	*new_input;
	int 	quotes_found;
	int		i;
	int		j;
	int		original_quote_pos;

	if (data->escaped)
	{
		data->escaped = false;
		return ;
	}
	original_quote_pos = *quote_pos;
	quote_type = *(data->input + *quote_pos);
	new_input = malloc(ft_strlen(data->input) - 2 * QUOTE_CHAR + 1);
	if (!new_input)
		terminate_program(MALLOC);
	quotes_found = 0;
	i = 0;
	j = 0;
	while (i != *quote_pos)
		new_input[j++] = data->input[i++];
	while (data->input[i] != '\0' && quotes_found < 2)
	{
		if (data->input[i] == quote_type && !is_escaped(data->input, i))
			(quotes_found)++;
		else
			new_input[j++] = data->input[i];
		i++;
	}
	if (quotes_found < 2)
	{
		free(new_input);
		terminate_program(UNCLOSED_QUOTES);
	}
	*quote_pos += j - QUOTE_CHAR;
	while (data->input[i] != '\0')
		new_input[j++] = data->input[i++];
	new_input[j] = '\0';
	free(data->input);
	data->input = new_input;
	if (quote_type == '\"')
		look_for_expansions(data, original_quote_pos, *quote_pos);
}


void	look_for_expansions(t_data *data, int i, int end)
{
	while (i < end)
	{
		if (is_escape_char(data->input[i])
		&& (is_dollar_sign(data->input[i + 1]) || data->input[i + 1] == '\"'))
			remove_escape_char(data, &i);
		else if (is_dollar_sign(data->input[i]))
			handle_dollar_sign(data, i);
		else
			data->escaped = false;
		i++;
	}
}
