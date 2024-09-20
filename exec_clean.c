/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/09/20 15:31:01 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"
#include "struct.h"

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
		return (2);
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

int	exec_builtin(char **arr_cmd)
{
	(void)arr_cmd;
	return (0);
}

int	prep_cmds(t_cmd *cmd, t_info *info, t_exec *exec_info)
{
	// expansion
	cmd->path = find_path(exec_info->paths, cmd->arr_cmd);
	if (!cmd->path)
		return (1);
	if (cmd->next) // quiero NO haga pipe para el último comando
	{
		pipe(exec_info->pipe_end);
		cmd->fd_out = exec_info->pipe_end[1];
		cmd->next->fd_in = exec_info->pipe_end[0];
	}
	return (0);
}

int	exec_mult_cmd(t_cmd *tmp, t_exec *exec_info, t_info *info)
{
	t_cmd	*cmd;

	cmd = tmp;
	while (cmd)
	{
		if (prep_cmds(cmd, info, exec_info) == 1)
			return (2);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (1);
		if (cmd->pid == 0)
			mult_child(cmd, info, exec_info);
		close(exec_info->pipe_end[1]); // cierro la parte de escritura de la pipe actual
		if (cmd->fd_in != -1) 
			close(cmd->fd_in); // cierro la parte de lectura de la pipe anterior 
		cmd = cmd->next;
	}
	close(exec_info->pipe_end[0]); // Tal vez, no es necesario.
	return (0);
}

int	exec_simp_cmd(t_cmd *cmd, t_info *info, t_exec *exec_info)
{
	if (prep_cmds(cmd, info, exec_info) == 1)
		return (2);
	/*if (!find_cmd_type(cmd->arr_cmd[0]))
	{
		open_redir(cmd);
		redirect(cmd);
		return (exec_builtin(cmd->arr_cmd));
	}*/
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
		simp_child_cmd(cmd, info, exec_info);
	waitpid(cmd->pid, &(info->ex_stat), 0);
	return (0);
}

int	set_exec_info(t_envp *envp, t_exec *exec_info)
{
	exec_info->env = envlst_to_arr(envp);
	if (!exec_info->env)
		return (1);
	exec_info->paths = prep_cmd_paths(exec_info->env);
	if (!exec_info->paths)
		return (1);
	exec_info->or_fd[0] = dup(0);
	exec_info->or_fd[1] = dup(1);
	return (0);
}

int	executor(t_cmd *segmts, t_info *info)
{
	t_cmd	*aux;
	t_exec	exec_info;

	if (!segmts)
		return (-1);
	if (set_exec_info(info->envp, &exec_info) == 1)
		return (-1);
	aux = segmts;
	find_heredocs(segmts);
	if (!segmts->next)
	{
		exec_simp_cmd(segmts, info, &exec_info);
		dup2(exec_info.or_fd[0], 0);
		dup2(exec_info.or_fd[1], 1);
		free_exec_info(&exec_info);
		return (WEXITSTATUS(info->ex_stat));
	}
	exec_mult_cmd(segmts, &exec_info, info);
	while (aux)
	{
		info->ex_stat = 0;
		waitpid(aux->pid, &info->ex_stat, 0);
	//	printf("%d en cmd con pid %d\n", WEXITSTATUS(info->ex_stat), aux->pid);
		aux = aux->next;
	}
	free_exec_info(&exec_info);
	return (WEXITSTATUS(info->ex_stat));
}


/*int	main(int argc, char **argv, char **env)
{
	(void)argc;
	t_info	info;
	t_exec	*exec_info;
	t_cmd	*cmds;

	exec_info = set_exec_info(env, argv[1]); // todos los posibles paths, or_fds, etc
	if (!exec_info)
		return (write(2, "issue exec_info\n", 16), 1);
	cmds = hardcore_commands(argv, env, exec_info->paths); // para findpath, get arr_cmd, etc
	if (!cmds)
	{
		write(2, "problem hardcoring cmds\n", 24);
		return (1);
	}
	printf("execution res: %d\n", executor(cmds, &info, exec_info));
	return (0);
}*/
