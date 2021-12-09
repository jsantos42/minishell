#include "../headers/escape_char.h"

bool	is_escape_char(char chr)
{
	return (chr == '\\');
}

bool	is_escaped(char *str, int i)
{
	return (i != 0 && str[i - 1] == '\\');
}

/*
**	Receives the str from which to remove the escape char, and the index of the
**	escaped character (NOT the '\\' itself, the next one). Returns the number of
**	chars removed.
*/

int	remove_escape_char(t_data *data, int *escaped_char)
{
	char	*new_input;
	int		i;
	int		j;

	if (data->escaped)
		return (escape(data, escaped_char));
	new_input = malloc(ft_strlen(data->input) - ESCAPECHAR + 1);
	i = 0;
	j = 0;
	while (data->input[i] != '\0')
	{
		if (i == *escaped_char)
			i++;
		else
			new_input[j++] = data->input[i++];
	}
	new_input[j] = '\0';
	data->escaped = true;
	free(data->input);
	data->input = new_input;
	return (1);
}

/*
**	This function is called if the data->escaped flag is on. If so, it turns off
**	the flag and advances the iterator.
*/

int	escape(t_data *data, int *i)
{
	data->escaped = false;
	(*i)++;
	return (0);
}
