/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_accessors.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:45:58 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 19:57:06 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_ACCESSORS_H
# define ENV_ACCESSORS_H

# include "../main.h"

int		update_env_var(char *key, char *new_value);

char	*get_env_var(char *key);

void	del_env_var(void *env_var_void);

#endif // !ENV_ACCESSORS_H