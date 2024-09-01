/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/09/01 18:29:16 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "execution.h"
#include "struct.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

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

int	open_redir_m(t_cmd *cmd)
{
	while (cmd->redirs)
	{
		if (cmd->redirs->token == INPUT)
		{
			write(2, "open con input\n", 15);
			cmd->fd_in = open(cmd->redirs->file_name, O_RDONLY);
			if (cmd->fd_in == -1)
			{
				perror(cmd->redirs->file_name);
				return (1);
			}
		}
		else if (cmd->redirs->token == APPEND)
		{
			write(2, "open con append\n", 16);
			cmd->fd_out = open(cmd->redirs->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (cmd->fd_out == -1)
			{
				perror(cmd->redirs->file_name);
				return (1);
			}
		}
		else if (cmd->redirs->token == OUTPUT)
		{
			write(2, "open con output\n", 16);
			cmd->fd_out = open(cmd->redirs->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd_out == -1)
			{
				perror(cmd->redirs->file_name);
				return (1);
			}
		}
		cmd->redirs = cmd->redirs->next;
	}
	return (0);
}

int	redirect_m(t_cmd *cmd)
{
//	fprintf(stderr, "inx: %d\nfd_in: %d\nfd_out: %d\n", cmd->indx, cmd->fd_in, cmd->fd_out);
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, 0) == -1)
		{
			write(2, "dup2 in failed\n", 15);
			return (1);
		}
		write(2, "paso por dup2 de in\n", 20);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
		{
			write(2, "dup2 out failed\n", 16);
			return (1);
		}
		write(2, "paso por dup2 de out\n", 21);
		close(cmd->fd_out);
	}
	return (0);
}

int	exec_builtin(char **arr_cmd)
{
	return (0);
}

int	exec_mult_cmd(t_cmd *cmd, t_exec *exec_info)
{
	while (cmd)
	{
		if (cmd->next) // quiero NO haga pipe para el último comando
		{
			pipe(exec_info->pipe_end); // cada vez que hago esto, reseteo los valores de los fds
			cmd->fd_out = exec_info->pipe_end[1];
			cmd->next->fd_in = exec_info->pipe_end[0];
		}
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (1);
		if (cmd->pid == 0)
		{
			if (open_redir_m(cmd) == 1)
				exit(0); // no sé qué num poner
			if (redirect_m(cmd) == 1)
				exit(0);
			close(exec_info->pipe_end[0]); // cierro el fd de lectura de la pipe ACTUAL
			if (find_cmd_type(cmd->arr_cmd[0]))
			{
				if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
				{
					write(2, "execve failed\n", 14);
					exit(127);
				}
			}
			exec_builtin(cmd->arr_cmd);
		}
		close(exec_info->pipe_end[1]); // cierro la parte de escritura de la pipe actual
		close(cmd->fd_in); // cierro la parte de lectura de la pipe anterior
		cmd = cmd->next;
	}
	close(exec_info->pipe_end[0]);
	return (0);
}

int	exec_simp_cmd(t_cmd *cmd, t_info *info)
{
	if (!find_cmd_type(cmd->arr_cmd[0]))
	{
		open_redir_m(cmd);
		redirect_m(cmd);
		return (exec_builtin(cmd->arr_cmd));
		// resertear STD_IN y STD_OUT a el 0 y 1 original
	}
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		if (open_redir_m(cmd) == 1)
			exit(1);
		if (redirect_m(cmd) == 1)
			exit(1); // ? nosee
		if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
		{
			write(2, "execve failed\n", 14);
			exit(127); //command not found
		}
	}
	waitpid(cmd->pid, &(info->ex_stat), 0);
	return (info->ex_stat);
}

int	find_heredocs(t_cmd *cmds)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_rdir;

	tmp_cmd = cmds;
	while (tmp_cmd)
	{
		if (tmp_cmd->redirs)
		{
			tmp_rdir = tmp_cmd->redirs;
			while (tmp_rdir)
			{
				if (tmp_rdir->token == HEREDOC)
				{
					//tmp_rdir->fd = heredoc(tmp_rdir->file_name);
					tmp_cmd->fd_in = heredoc(tmp_rdir->file_name);
				}
				tmp_rdir = tmp_rdir->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

t_exec *set_exec_info(char **env, char *rl)
{
	t_exec	*exec_info;

	exec_info = malloc(sizeof(t_exec) * 1);
	if (!exec_info)
		return (NULL);
	exec_info->paths = prep_cmd_paths(env);
	if (!exec_info->paths)
		return (NULL);
	exec_info->or_fd[0] = dup(0);
	exec_info->or_fd[1] = dup(1);
//	exec_info->cmd_num = count_cmds(rl);
	exec_info->cmd_num = 4;
	return (exec_info);
}

void	print_cmds(t_cmd *cmds)
{
	while (cmds)
	{
		printf("CMD\narr_cmd[0]: %s, arr_cmd[1]: %s\npath: %s\nfd_in: %d, fd_out: %d\nredirs: %p\nindex: %d\n", cmds->arr_cmd[0], cmds->arr_cmd[1], cmds->path, cmds->fd_in, cmds->fd_out, cmds->redirs, cmds->indx);
		cmds = cmds->next;
	}
}

t_cmd	*hardcore_commands(char **argv, char **env, char **paths)
{
	t_cmd	*cmds;
	t_cmd	*cmd2;
	t_cmd	*cmd3;
	t_cmd	*cmd4;
//	t_redir	*tmp;
	char	**arr_cmd;
	char	**arr_cmd2;
	char	**arr_cmd3;
	char	**arr_cmd4;

	cmds = malloc(sizeof(t_cmd) * 1);
	if (!cmds)
		return (NULL);
	arr_cmd = malloc(sizeof(char *) * 2);
	if (!arr_cmd)
		return (NULL);
	arr_cmd[0] = argv[3];
	arr_cmd[1] = NULL;
	cmds->arr_cmd = arr_cmd;
	cmds->path = find_path(paths, cmds->arr_cmd);
	cmds->env = env;
	cmds->fd_in = -1;
	cmds->fd_out = -1;
//	cmds->redirs = NULL;
	cmds->indx = 1;
	cmds->next = NULL;

	cmds->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmds->redirs)
		return (NULL);
	cmds->redirs->token = HEREDOC;
	cmds->redirs->file_name = argv[2];
	cmds->redirs->fd = -1;
	cmds->redirs->next = NULL;

	cmd2 = malloc(sizeof(t_cmd) * 1);
	if (!cmd2)
		return (NULL);
	arr_cmd2 = malloc(sizeof(char *) * 2);
	if (!arr_cmd2)
		return (NULL);
	arr_cmd2[0] = malloc(sizeof(char) * (ft_strlen(argv[3]) + 1));
	if (!arr_cmd2[0])
		return (NULL);
	arr_cmd2[0] = argv[5];
	arr_cmd2[1] = NULL;
	cmd2->arr_cmd = arr_cmd2;
	cmd2->path = find_path(paths, cmd2->arr_cmd);
	cmd2->env = env;
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->redirs = NULL;
	cmd2->indx = 2;
	cmd2->next = NULL;

//	cmds->next = cmd2;

	cmd3 = malloc(sizeof(t_cmd) * 1);
	if (!cmd3)
		return (NULL);
	arr_cmd3 = malloc(sizeof(char *) * 2);
	if (!arr_cmd3)
		return (NULL);
	arr_cmd3[0] = malloc(sizeof(char) * (ft_strlen(argv[5]) + 1));
	if (!arr_cmd3[0])
		return (NULL);
	arr_cmd3[0] = argv[7];
	arr_cmd3[1] = NULL;
	cmd3->arr_cmd = arr_cmd3;
	cmd3->path = find_path(paths, cmd3->arr_cmd);
	cmd3->env = env;
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->redirs = NULL;
	cmd3->indx = 3;
	cmd3->next = NULL;

//	cmd2->next = cmd3;

	cmd4 = malloc(sizeof(t_cmd) * 1);
	if (!cmd4)
		return (NULL);
	arr_cmd4 = malloc(sizeof(char *) * 2);
	if (!arr_cmd4)
		return (NULL);
	arr_cmd4[0] = malloc(sizeof(char) * (ft_strlen(argv[3]) + 1));
	if (!arr_cmd4[0])
		return (NULL);
	arr_cmd4[0] = argv[9];
	arr_cmd4[1] = NULL;
	cmd4->arr_cmd = arr_cmd4;
	cmd4->path = find_path(paths, cmd4->arr_cmd);
	cmd4->env = env;
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
//	cmd4->redirs = NULL;
	cmd4->indx = 4;
	cmd4->next = NULL;

	cmd4->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd4->redirs)
		return (NULL);
	cmd4->redirs->token = HEREDOC;
	cmd4->redirs->file_name = argv[11];
	cmd4->redirs->fd = -1;
	cmd4->redirs->next = NULL;
	
/*	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->token = OUTPUT;
	tmp->file_name = argv[11];
	tmp->fd = -1;
	tmp->next = NULL;

	cmd4->redirs->next = tmp;*/

	//cmd3->next = cmd4;

//	print_cmds(cmds);
//	print_redirs_lst(cmds->redirs);
	return (cmds);
}

int	executor(t_cmd *segmts, t_info *info, t_exec *exec_info)
{
	int	i;

	i = 0;
	find_heredocs(segmts);
	if (!segmts->next)
		return (WEXITSTATUS(exec_simp_cmd(segmts, info)));
	if (segmts)
	{
		exec_mult_cmd(segmts, exec_info);
	}
	while (i < exec_info->cmd_num)
	{
		waitpid(segmts->pid, &info->ex_stat, 0);
		i++;
	}
	return (WEXITSTATUS(info->ex_stat));
}

//   --  ./a.out      cat       "|"        cat       "|"       cat   --
//       argv[0]   argv[1]    argv[2]    argv[3]   argv[4]   argv[5]      argv[6]

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_exec	*exec_info;
	t_cmd	*cmds;

	exec_info = set_exec_info(env, argv[1]); // todos los posibles paths, or_fds, etc
	cmds = hardcore_commands(argv, env, exec_info->paths); // para findpath, get arr_cmd, etc
	if (!cmds)
	{
		write(2, "problem hardcoring cmds\n", 24);
		return (1);
	}
	printf("execution res: %d\n", executor(cmds, &info, exec_info));
	return (0);
}
