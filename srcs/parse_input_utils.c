#include "../headers/parse_input_utils.h"

void	skip_white_space(char *input, int *i)
{
	while (input[*i] != '\0' && ft_isspace(input[*i]))
		(*i)++;
}



char	*parser_core(t_data *data, int *i, t_flags *flags)
{
	int old_i;
	char *str;

	old_i = *i;
	while (data->input[*i] != '\0' && (!ft_isspace(data->input[*i])
									   || (ft_isspace(data->input[*i]) && data->escaped)))
	{
		if (is_escape_char(data->input[*i]))
			remove_escape_char(data, i);
		else if (is_quote_char(data->input[*i]))
			handle_quote_char(data, i);
		else if (is_dollar_sign(data->input[*i]) && flags->interpret_dollar)
			handle_dollar_sign(data, i);
		else if (is_special_char(data->input[*i])) //missing protection against escape here
		{
			if (data->escaped)
			{
				data->escaped = false;
				(*i)++;
			}
			else
				break;
		}
		else if (is_semicomma(data->input[*i]))
		{
			if (data->escaped)
			{
				data->escaped = false;
				(*i)++;
			}
			else
				terminate_program(SPECIAL_CHAR);
		}
		else
		{
			data->escaped = false;
			(*i)++;
		}
	}
	str = NULL;
	if (*i != old_i)
		str = ft_substr(data->input, old_i, *i - old_i);
	return (str);
}
