/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/08/21 15:18:44 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"


// ----  cat | ls ----

void	redir_to_pipes(t_cmd *cmd, t_exec *exec_info)
{
	if (!cmd->next && exec_info)
		if (dup2(exec_info->pipe_end[1], 1) == 1)
			return (write(2, "dup2 in pipe redirs failed\n", 27));
	else if (cmd->next)
}

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

int	exec_mult_cmd(t_exec *cmd)
{
	pipe(&(exec_info->pipe_end)); // cada vez que hago esto, reseteo los valores de los fds
	seg_tmp.pid = fork();
	if (seg_tmp.pid == -1)
		return (1);
	if (seg_tmp.pid == 0)
	{
		// dup2 de pipes en hijo
		redir_to_pipes(seg_tmp, exec_info);
			// -> si es el 1er comando, hago solo dup2 de 1 a la pipe[1]
			// -> si es comando etre otros, hago dup2 de 0 a la pipe[0] anterior y de 1 a la pipe[1] actual
		// dup2 de redirs en hijo
		// execve
		// close fds de pipe_end que no se hayan usado?
		exec_cmd;
}

int	exec_simp_cmd(t_exec *cmd, t_info *info)
{
	cmd->pid = fork();
	if (!cmd->pid)
		return (0);
	if (cmd->pid == 0)
	{
		redirect(cmd->redirs);
		if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
		{
			write(2, "execve failed\n", 14);
			info->ex_stat = 1;
			exit(1);
		}
	}
	return (1);
}

int	executor(t_cmd *segmts, t_info *info, t_exec *exec_info)
{
	t_cmd	*seg_tmp;

	seg_tmp = segmts;
	while (seg_tmp)
	{
		// set_command(); para findpath, etc
		// crear heredoc y me devuelve fd

		// SI HAY MÁS CMDS
		if (seg_tmp->next)
			exec_mult_cmd();
		
		// SI SOLO HAY UN CMD Y ES CMD
		else if (!seg_tmp->next && find_cmd_type(seg_tmp->arr_cmd[0]))
		{
			exec_simp_cmd(seg_tmp, info);
		}
		// close en padre de las partes de la pipe no utilizadas?
		
		// SI HAY UN CMD Y ES BUILTIN
		else if (!seg_tmp->next && !find_cmd_type(seg_tmp->arr_cmd[0]))
		{
			// redirs con dup2 en padre
			exec_builtin;
			// resertear STD_IN y STD_OUT a el 0 y 1 original
		}
		seg_tmp = seg_tmp->next;
	}
	return (info->ex_stat);
}
