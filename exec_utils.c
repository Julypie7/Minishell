/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:39:55 by martalop          #+#    #+#             */
/*   Updated: 2024/09/09 16:50:48 by martalop         ###   ########.fr       */
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

void	print_redirs_lst(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		printf("redir[%p]\ntoken: %d\nfile_name: %s\nfd: %d\nnext: %p\n\n", tmp, tmp->token, tmp->file_name, tmp->fd, tmp->next);
		tmp = tmp->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*aux;
	int		i;

	aux = cmds;
	while (aux)
	{
		printf("CMD[%p]\narr_cmd: %p\npath: %s\npid : %d\nfd_in: %d, fd_out: %d\nredirs: %p\nindex: %d\nnext: %p\n", aux, aux->arr_cmd, aux->path, aux->pid, aux->fd_in, aux->fd_out, aux->redirs, aux->indx, aux->next);
		i = 0;
		while (aux->arr_cmd[i])
		{
			printf("arr_cmd[%d]: %s\n", i, aux->arr_cmd[i]);
			i++;
		}
		print_redirs_lst(aux->redirs);
		write(2, "\n", 1);
		aux = aux->next;
	}
}
