/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/08/23 19:19:01 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"
#include "struct.h"

// ----  cat | ls ----

int	fill_arr_b(char **arr_b)
{
	const char	*builtins[8];
	int			i;

	i = 0;
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
	builtins[7] = NULL;
	while (builtins[i])
	{
		arr_b[i] = malloc(sizeof(ft_strlen(builtins[i]) + 1));
		if (!arr_b[i])
		{
			free_array(arr_b);
			write(2, "malloc error\n", 13);
			return (2);
		}
		ft_strlcpy(arr_b[i], builtins[i], ft_strlen(builtins[i]) + 1);
		i++;
	}
	arr_b[i] = NULL;
	return (1);
}

int	find_cmd_type(char *str)
{
	char	**arr_b;
	int		i;

	i = 0;
	if (!str)
		return ;
	arr_b = malloc(sizeof(char *) * 8);
	if (!arr_b || fill_arr_b(arr_b) == 2)
		return (2);
	while (arr_b[i])
	{
		if (!ft_strncmp(str, arr_b[i], ft_strlen(arr_b[i]) + 1))
		{
			free_array(arr_b);
			return (0); // es builtin
		}
		i++;
	}
	free_array(arr_b);
	return (1); // es cmd
}

int	redir_to_pipes(t_cmd *cmd, t_exec *exec_info)
{
	if (!cmd->next) // es el ultimo cmd
	{
		if (dup2(exec_info->pipe_end[0], 0) == 1) // lee de la pipe anterior
			return (write(2, "dup2 in pipe redirs failed\n", 27), 1);
		else
			close(exec_info->pipe_end[0]);
	}
	else if (cmd->next)
	{
		if (exec_info->cmd_num != 0) // es un cmd en medio de otros
		{
			if (dup2(exec_info->pipe_end[0], 0) == 1) // lee de la pipe anterior
				return (write(2, "dup2 in pipe redirs failed\n", 27), 1);
			else
				close(exec_info->pipe_end[0]);
		}
		if (dup2(exec_info->pipe_end[1], 1) == 1) // escribe en la pipe actual
			return (write(2, "dup2 in pipe redirs failed\n", 27), 1);
		else
	}
}

int	exec_mult_cmd(t_exec *cmd)
{
	while (cmd)
	{
		if (cmd->next) // quiero NO haga pipe para el último comando
		{
			pipe(exec_info->pipe_end); // cada vez que hago esto, reseteo los valores de los fds
		//	prev_pipe_fdr = exec_info->pipe_end[0];
			cmd->fd_out = exec_info->pipe_end[1];
			cmd->next->fd_in = exec_info->pipe_end[0];
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (1);
		if (cmd->pid == 0)
		{
			// dup2 de pipes en hijo
			redir_to_pipes(cmd, exec_info);
				// -> si es el 1er comando, hago solo dup2 de 1 a la pipe[1]
				// -> si es comando etre otros, hago dup2 de 0 a la pipe[0] anterior y de 1 a la pipe[1] actual
				// -> si es el ultimo comando, hago dup de 0 a la pipe[0] anterior
			// dup2 de redirs en hijo
			open_redir(cmd->redirs);
			redirect(cmd->redirs);
			// preguntarme si es builtin o no
			if (find_cmd_type(cmd))
			{
				if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
				{
					write(2, "execve failed\n", 14);
					exit(1);
				}
			}
			else
				exec_builtin(cmd);
		}
		close(pipe_end[1]); // cierro la parte de escritura de la pipe actual
		cmd = cmd->next;
	}
}

int	exec_simp_cmd(t_cmd *cmd, t_info *info)
{
	if (!find_cmd_type(cmd->arr_cmd[0]))
	{
		open_redir(cmd->redirs);
		redirect(cmd->redirs);
		return (exec_builtin(cmd->arr_cmd, info));
		// resertear STD_IN y STD_OUT a el 0 y 1 original
	}
	cmd->pid = fork();
	if (!cmd->pidc)
		return (0);
	if (cmd->pid == 0)
	{
		//heredoc
		open_redir(cmd->redir);
		redirect(cmd->redirs);
		if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
		{
			write(2, "execve failed\n", 14);
			exit(1);
		}
	}
	waitpid(cmd->pid, &(info->ex_stat), 0);
	return (1);
}

int	find_heredocs(t_cmd *cmds)
{
	t_cmd	tmp_cmd;

	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		if (tmp_cmd->redirs)
		{
			while (tmp_cmd->redirs)
			{
				if (tmp_cmd->redirs->type == HEREDOC)
					tmp_cmd->redirs->fd = heredoc(tmp_cmd->redirs->file_name);
				tmp_cmd->redirs = tmp_cmd->redirs->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
}

int	executor(t_cmd *segmts, t_info *info, t_exec *exec_info)
{
	// set_exec_info(); todos los posibles paths, or_fds, etc
	// set_commands(); para findpath
	if (!segmts->next)
		return (exec_simp_cmd(segmts, info));
	while (segmts)
	{
		exec_mult_cmd(segmts, info);
		segmts = segmts->next;
	}
	// while de waits?
	return (info->ex_stat);
}
