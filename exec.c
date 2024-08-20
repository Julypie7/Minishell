/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/08/20 13:28:11 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"


// ----  cat | ls ----

/*int	do_heredocs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		tmp->fd = heredoc(tmp->file_name);
		tmp = tmp->next;
	}
}*/

void	redir_to_pipes(t_cmd *cmd, t_exec *exec_info)
{
	if (!cmd->next && exec_info)
		if (dup2(exec_info->pipe_end[1], 1) == 1)
			return (write(2, "dup2 in pipe redirs failedv\n", 28));
	else if (cmd->next)
}

int	executor(t_cmd *segmts, t_info *info, t_exec *exec_info)
{
	t_cmd	*seg_tmp;

	seg_tmp = segmts;
	// cat en la primera pasada, ls en la segunda
	while (seg_tmp)
	{
		// set_command(); para findpath, etc
		if (seg_tmp->next || (!seg_tmp->next && find_cmd_type(seg_tmp->arr_cmd[0])))
		{
			// crear pipe
			if (seg_tmp->next)
				pipe(&(exec_info->pipe_end)); // cada vez que hago esto, reseteo los valores de los fds
			// heredoc
				//fd = heredoc(??) // create and write in heredoc pipe
			// fork
			seg_tmp.pid = fork();
			if (seg_tmp.pid == -1)
				return (1);
			if (seg_tmp.pid == 0)
			{
				// dup2 de pipes en hijo
				redir_to_pipes(seg_tmp, exec_info);
					// -> si es el 1er comando, hago solo dup2 de 1 a la pipe[1]
					// -> si es comando etre otros, hago dup2 de 0 a la pipe[0] anterior y de 1 a la pipe[1] actual
					// -> si es último comando, hago solo dup2 de 0 a la pipe[0]
				// dup2 del fd de lectura del heredoc
				// dup2 de redirs en hijo
				// execve
				// close fds de pipe_end que no se hayan usado?
				exec_cmd;
			}
			// close en padre de las partes de la pipe no utilizadas?
		}
		else if (!seg_tmp->next && !find_cmd_type(seg_tmp->arr_cmd[0]))
		{
			// no fork
			// heredoc
			// redirs con dup2 en padre
			// no execve
			exec_builtin;
			// resertear STD_IN y STD_OUT a el 0 y 1 original
		}
		seg_tmp = seg_tmp->next;
	}
	return (info->ex_stat);
}
