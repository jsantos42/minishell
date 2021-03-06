/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsantos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:45:44 by jsantos           #+#    #+#             */
/*   Updated: 2021/12/13 14:48:19 by jsantos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOLLAR_SIGN_H
# define DOLLAR_SIGN_H

# include "../main.h"
# define  DOLLAR_SIGN 1

typedef struct s_dollar {
	char	*name;
	char	*expanded;
	int		name_len;
	int		expanded_len;
	bool	expand_status;
}	t_dollar;

bool	is_dollar_sign(char chr);
int		handle_dollar_sign(t_data *data, int *dollar_pos);
int		get_var_length(char *var);
void	get_expanded_var(t_dollar *d, int status);
char	*replace_input(char *original, t_dollar *dollar, int dollar_pos);

#endif
