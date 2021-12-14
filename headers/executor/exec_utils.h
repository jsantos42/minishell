/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 19:45:49 by pbielik           #+#    #+#             */
/*   Updated: 2021/12/13 19:45:50 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_UTILS_H
# define EXEC_UTILS_H

# include "../main.h"

char	*get_cmd_path(char *cmd);

void	open_io_files(t_leaf_node *leaf, int *ctx);

void	ft_close_fds(t_leaf_node *leaf, int *ctx);

#endif // !EXEC_UTILS_H