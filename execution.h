/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:10 by martalop          #+#    #+#             */
/*   Updated: 2024/08/01 22:14:11 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_cmd
{
	char	**arr_cmd;
 	char	*path;
 	char	**env;
 	int		redir[4];
	int		pid;
//	expansion ?
}	t_cmd_info;

#endif
