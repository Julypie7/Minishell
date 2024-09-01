/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:39:55 by martalop          #+#    #+#             */
/*   Updated: 2024/09/01 21:04:31 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "execution.h"

void	free_exec_info(t_exec *exec_info)
{
	free_array(exec_info->paths);
	free(exec_info);
}

void	free_redir_lst(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		tmp = tmp->next;
//		free(redirs->file_name);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		tmp = tmp->next;
		free_array(cmds->arr_cmd);
		free(cmds->path);
	//	free_array(env);
		if (cmds->redirs)
			free_redir_lst(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}
