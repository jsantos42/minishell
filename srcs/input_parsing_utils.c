#include "../headers/input_parsing_utils.h"

bool	is_special_char(char chr)
{
	if (chr == '|' || chr == '&' || chr == '<' || chr == '>'
	|| chr == '\\' || chr == ';')
		return (true);
	else
		return (false);
}

bool	is_quote_char(char chr)
{
	return (chr == '\'' || chr == '\"');
}

bool	is_dollar_char(char chr)
{
	return (chr == '$');
}


/*
**	This makes sure nothing between quotes gets interpreted as a command. It
**	starts by defining which type of quote it's using and runs through the
**	string str. When it reaches the same quote char, as long as it wasn't
**	escaped, it returns the number of iterations made.
**
**	NOTE1: it starts checking on index 1 (since index 0 is the opening quote)
**	and, as such, it does not require a safety check for a negative index when
**	doing the operation str[iter - 1].
**	NOTE2: the return (0) line at the end of the function is actually redundant,
**	but the compiler does raise an error if it's not there.
*/

int	advance_to_closing_quote(char *str)
{
	char	quote_type;
	int		iter;

	quote_type = *str;
	iter = 0;
	while (str[++iter] != '\0')
	{
		if (str[iter] == quote_type && str[iter - 1] != '\\')
			return (iter);
	}
	terminate_program(UNCLOSED_QUOTES);
	return (0);
}



if (scanner->cursor[iter] == '\"' || scanner->cursor[iter] == '\'')
scanner->cursor = handle_quote(scanner->cursor, &iter);

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
**	NOTE: when saving the new quote_pos, it uses kter (instead of iter) because
**	it needs to subtract 2 quote chars from the index count. Plus, it needs to
**	subtract 1 because the iteration on the previous while goes one extra loop.
*/

char	*handle_quote(char *input, int *quote_pos)
{
	char	quote_type;
	char	*new_input;
	int 	quotes_found;
	int		iter;
	int		kter;

	quote_type = *(input + *quote_pos);
	new_input = malloc(ft_strlen(input) - PAIR_OF_QUOTES + 1);
	if (!new_input)
		terminate_program(MALLOC);
	quotes_found = 0;
	iter = 0;
	kter = 0;
	while (input[iter] != '\0' && quotes_found < 2)
	{
		if (!(input[iter] == quote_type
			  && (iter == 0 || input[iter - 1] != '\\')))
			new_input[kter++] = input[iter];
		else
			(quotes_found)++;
		iter++;
	}
	if (quotes_found < 2)
	{
		free(new_input);
		terminate_program(UNCLOSED_QUOTES);
	}
	else
	{
		*quote_pos += kter - 1;
		while (input[iter] != '\0')
			new_input[kter++] = input[iter++];
		new_input[kter] = '\0';
	}
	return (new_input);
}
