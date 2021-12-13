/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:50:45 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 16:50:46 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/built-ins/__pwd.h"

int	__pwd(char **args, int *ctx)
{
	char	*cwd;

	(void)args;
	(void)ctx;
	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
