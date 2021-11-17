#include "../headers/dollar_sign.h"

bool	is_dollar_sign(char chr)
{
	return (chr == '$');
}

char	*handle_dollar_sign(char *input, int *dollar_pos)
{
	//this must finish on a space or special char
	(void)input;
	(void)dollar_pos;
	return (input);//must return new_input
}
