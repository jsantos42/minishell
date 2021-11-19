#include "../headers/dollar_sign.h"

bool	is_dollar_sign(char chr)
{
	return (chr == '$');
}

void	handle_dollar_sign(t_data	*data, int dollar_pos)
{
	char	*expanded_var;
	size_t	new_input_size;
	char	*new_input;
	int		i;
	int		j;
	int		k;

//	this protection against escape should make the special char part of the argument
//	if (dollar_pos != 0 && --dollar_pos == '\\')
//		return ;
	if (dollar_pos == 0 || --dollar_pos != '\\')
	{
		expanded_var = get_expanded_var(
				data);// get string corresponding to variable to expand (protect against failure)
		new_input_size = ft_strlen(data->input) + ft_strlen(expanded_var) - DOLLAR_SIGN;
		new_input = malloc(new_input_size + 1);
		if (!new_input)
			terminate_program(MALLOC);
		i = 0;
		k = 0;
		while (data->input[i] != '\0' && input[i] != '$')
			new_input[k++] = input[i++];
		i++;
		j = 0;
		while (expanded_var[j] != '\0')
			new_input[k++] = expanded_var[j++];
		while (input[i] != '\0')
			new_input[k++] = input[i++];
		new_input[k] = '\0';
		free(input);

		//this must finish on a space or special char
		(void) input;
		(void) dollar_pos;
		return (input);//must return new_input
	}
}
