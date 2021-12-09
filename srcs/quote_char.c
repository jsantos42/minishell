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
**	NOTE: when saving the new opening_quote, it uses j (instead of i) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

void	handle_quote_char(t_data *data, int *opening_quote)
{
	char	quote_type;
	char	*new_input;
	int		i;
	int		j;
	int		closing_quote;

	if (data->escaped)
	{
		(*opening_quote)++;
		data->escaped = false;
		return ;
	}
	quote_type = *(data->input + *opening_quote);
	closing_quote = 0;
	i = *opening_quote;
	while (!closing_quote && data->input[++i] != '\0')
	{
		if (data->input[i] == quote_type && !is_escaped(data->input, i))
			closing_quote = i;
	}
	if (!closing_quote)
		terminate_program(UNCLOSED_QUOTES);
	if (quote_type == '\"')
		look_for_expansions(data, *opening_quote, &closing_quote);
	new_input = malloc(ft_strlen(data->input) - 2 * QUOTE_CHAR + 1);
	if (!new_input)
		terminate_program(MALLOC);
	i = -1;
	j = -1;
	while (data->input[++i] != '\0')
	{
		if (i == *opening_quote || i == closing_quote)
			continue ;
		new_input[++j] = data->input[i];
		if (i > *opening_quote && i <= closing_quote)
			(*opening_quote)++;
	}
	new_input[++j] = '\0';
	free(data->input);
	data->input = new_input;
}


/*
**	If the input string is changed, both the iterator i (initially marking the
**	opening_quote position) and the end (marking the closing quote position)
**	must change too.
*/

void	look_for_expansions(t_data *data, int i, int *end)
{
	while (i < *end)
	{
		if (is_escape_char(data->input[i])
		&& (is_dollar_sign(data->input[i + 1]) || data->input[i + 1] == '\"'))
			*end -= remove_escape_char(data, &i);
		else if (is_dollar_sign(data->input[i]))
			*end += handle_dollar_sign(data, &i);
		else
		{
			data->escaped = false;
			i++;
		}
	}
}
