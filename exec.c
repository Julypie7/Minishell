/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/08/13 19:45:22 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"

int	executor(t_cmd *segmts, t_info *info)
{
	t_cmd	*seg_tmp;

	seg_tmp = segmts;
	while (seg_tmp)
	{
		if (seg_tmp->next)
		{

		}
		else if (!seg_tmp->next && find_cmd_type)
		{
			exec_single_cmd;
		}
		else if (!seg_tmp->next && !find_cmd_type)
			exec_builtin;

	}
	return (info->ex_stat);
}
