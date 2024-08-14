/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/08/14 20:56:20 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"


// ----  cat | ls ----

// h

int	do_heredocs(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		tmp->fd = heredoc(tmp->file_name);
		tmp = tmp->next;
	}
}

int	executor(t_cmd *segmts, t_info *info, t_exec *exec_info)
{
	t_cmd	*seg_tmp;

	seg_tmp = segmts;
	// cat en la primera pasada, ls en la segunda
	while (seg_tmp)
	{
		// set_command(); para findpath, etc
		if (seg_tmp->next || (!seg_tmp->next && find_cmd_type))
		{
			// crear pipe
			pipe(&(exec_info->pipe_end));
			// heredoc
			do_heredocs(seg_tmp->redirs); // create and write in heredoc pipe
			// fork
			// dup2 de pipes en hijo
				// -> si es el 1er comando, hago solo dup2 de 1 a la pipe[0]
				// -> si es comando etre otros, hago dup2 de 0 a la pipe[0] anterior y de 1 a la pipe[1] actual
				// -> si es último comando, hago solo dup2 de 0 a la pipe[0]
			// dup2 del fd de lectura del heredoc
			// dup2 de redirs en hijo
			// execve
			// close fds de pipe_end que no se hayan usado?
			exec_cmd;
		}
		else if (!seg_tmp->next && !find_cmd_type)
		{
			// no fork
			// dup2 en padre
			// no execve
			exec_builtin;
			// resertear STD_IN y STD_OUT a el 0 y 1 original
		}
		seg_tmp = seg_tmp->next;
	}
	return (info->ex_stat);
}
