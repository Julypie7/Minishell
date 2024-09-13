/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:14:49 by martalop          #+#    #+#             */
/*   Updated: 2024/09/13 16:10:03 by martalop         ###   ########.fr       */
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
	t_redir	*tmp;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == INPUT)
		{
			close(cmd->fd_in);
//			write(2, "open con input\n", 15);
			cmd->fd_in = open(tmp->file_name, O_RDONLY);
			if (cmd->fd_in == -1)
			{
				perror(tmp->file_name);
				return (1);
			}
		}
		else if (tmp->type == APPEND)
		{
			close(cmd->fd_out);
//			write(2, "open con append\n", 16);
			cmd->fd_out = open(tmp->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (cmd->fd_out == -1)
			{
				perror(tmp->file_name);
				return (1);
			}
		}
		else if (tmp->type == OUTPUT)
		{
//			write(2, "open con output\n", 16);
			close(cmd->fd_out);
			cmd->fd_out = open(tmp->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd_out == -1)
			{
				perror(tmp->file_name);
				return (1);
			}
		}
		else if (tmp->type == HEREDOC)
		{
			close(cmd->fd_in);
			cmd->fd_in = tmp->fd;
			tmp->fd = -1;
			if (cmd->fd_in == -1)
			{
				perror(tmp->file_name);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redirect_m(t_cmd *cmd)
{
//	dprintf(2, "inx: %d\nfd_in: %d\nfd_out: %d\n", cmd->indx, cmd->fd_in, cmd->fd_out);
	if (cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, 0) == -1)
		{
			write(2, "dup2 in failed\n", 15);
			return (1);
		}
	//	write(2, "paso por dup2 de in\n", 20);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, 1) == -1)
		{
			write(2, "dup2 out failed\n", 16);
			return (1);
		}
	//	write(2, "paso por dup2 de out\n", 21);
		close(cmd->fd_out);
	}
	return (0);
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
	return (0);
}

int	exec_mult_cmd(t_cmd *tmp, t_exec *exec_info, t_info *info)
{
	(void)info;
	t_cmd	*cmd;
	int i;

	i = 1;
	cmd = tmp;
	while (cmd)
	{
		cmd->path = find_path(exec_info->paths, cmd->arr_cmd); // Cambiar a ponerlo en un lugar más bonito
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
			{
				free_exec_info(exec_info);
				free_cmds(cmd);
				exit(1); // no sé qué num poner
			}
			if (redirect_m(cmd) == 1)
				exit(1);
			close(exec_info->pipe_end[0]); // cierro el fd de lectura de la pipe ACTUAL |PODRIAS PASARLE ESTE FD A REDIRECT
			if (!cmd->arr_cmd)
				exit(0);
			if (!find_cmd_type(cmd->arr_cmd[0]))
				exec_builtin(cmd->arr_cmd);
			if (execve(cmd->path, cmd->arr_cmd, exec_info->env) == -1)
			{
				cmd_not_found(cmd->path);
				free_cmds(tmp);
				free_exec_info(exec_info);
				exit(127);
			}
		}
		close(exec_info->pipe_end[1]); // cierro la parte de escritura de la pipe actual
		if (cmd->fd_in != -1) 
			close(cmd->fd_in); // cierro la parte de lectura de la pipe anterior 
		cmd = cmd->next;
		i++;
	}
	close(exec_info->pipe_end[0]); // Tal vez, no es necesario.
	return (0);
}

int	exec_simp_cmd(t_cmd *cmd, t_info *info, t_exec *exec_info)
{
	if (prep_cmds(cmd, info, exec_info) == 1)
		return (2);
//	cmd->path = find_path(exec_info->paths, cmd->arr_cmd); 
//	cmd->env = info->mvp;
	/*if (!find_cmd_type(cmd->arr_cmd[0]))
	{
		open_redir_m(cmd);
		redirect_m(cmd);
		return (exec_builtin(cmd->arr_cmd));
	}*/
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		if (open_redir_m(cmd) == 1)
			exit(1); // ??
		if (!cmd->arr_cmd)
			exit(0);
		if (redirect_m(cmd) == 1)
			exit(1);
		if (execve(cmd->path, cmd->arr_cmd, exec_info->env) == -1)
		{
			cmd_not_found(cmd->path);
			exit(127);
		}
	}
	waitpid(cmd->pid, &(info->ex_stat), 0);
	return (0);
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
				if (tmp_rdir->type == HEREDOC)
				{
					tmp_rdir->fd = heredoc(tmp_rdir->file_name);
				//	tmp_cmd->fd_in = heredoc(tmp_rdir->file_name);
				}
				tmp_rdir = tmp_rdir->next;
			}
		}
		tmp_cmd = tmp_cmd->next;
	}
	return (0);
}

int	set_exec_info(t_envp *envp, t_exec *exec_info)
{
	char	**env;

	exec_info->env = envlst_to_arr(envp);
	if (!exec_info->env)
		return (1);
	exec_info->paths = prep_cmd_paths(exec_info->env);
	if (!exec_info->paths)
		return (1);
	exec_info->or_fd[0] = dup(0);
	exec_info->or_fd[1] = dup(1);
//	exec_info->cmd_num = count_cmds(rl);
	return (0);
}

t_cmd	*hardcore_commands(char **argv, char **env, char **paths)
{
	t_cmd	*cmds;
//	t_cmd	*cmd2;
//	t_cmd	*cmd3;
//	t_cmd	*cmd4;
//	t_redir	*tmp;
//	t_redir	*tmp2;
	char	**arr_cmd;
//	char	**arr_cmd2;
//	char	**arr_cmd3;
//	char	**arr_cmd4;

	cmds = malloc(sizeof(t_cmd) * 1);
	if (!cmds)
		return (NULL);
	arr_cmd = malloc(sizeof(char *) * 3);
	if (!arr_cmd)
		return (NULL);
	arr_cmd[0] = malloc(sizeof(char) * (ft_strlen(argv[1]) + 1));
	if (!arr_cmd[0])
		return (NULL);
	ft_strlcpy(arr_cmd[0], argv[1], (ft_strlen(argv[1]) + 1));
	arr_cmd[1] = malloc(sizeof(char) * (ft_strlen(argv[2]) + 1));
	if (!arr_cmd[1])
		return (NULL);
	ft_strlcpy(arr_cmd[1], argv[2], (ft_strlen(argv[2]) + 1));
	arr_cmd[2] = NULL;
	cmds->arr_cmd = arr_cmd;
	cmds->path = find_path(paths, cmds->arr_cmd);
	//cmds->env = env;
	cmds->fd_in = -1;
	cmds->fd_out = -1;
	cmds->redirs = NULL;
	cmds->indx = 1;
	cmds->next = NULL;

/*	cmds->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmds->redirs)
		return (NULL);
	cmds->redirs->type = INPUT;
	cmds->redirs->file_name = argv[4];
	cmds->redirs->fd = -1;
	cmds->redirs->next = NULL;*/

/*	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->type = OUTPUT;
	tmp->file_name = argv[7];
	tmp->fd = -1;
	tmp->next = NULL;

	cmds->redirs->next = tmp;*/
	
/*	tmp2 = malloc(sizeof(t_redir) * 1);
	if (!tmp2)
		return (NULL);
	tmp2->type = OUTPUT;
	tmp2->file_name = argv[7];
	tmp2->fd = -1;
	tmp2->next = NULL;

	tmp->next = tmp2;*/

/*	cmd2 = malloc(sizeof(t_cmd) * 1);
	if (!cmd2)
		return (NULL);
	arr_cmd2 = malloc(sizeof(char *) * 2);
	if (!arr_cmd2)
		return (NULL);
	arr_cmd2[0] = malloc(sizeof(char) * (ft_strlen(argv[6]) + 1));
	if (!arr_cmd2[0])
		return (NULL);
	ft_strlcpy(arr_cmd2[0], argv[6], (ft_strlen(argv[6]) + 1));
	arr_cmd2[1] = NULL;
	cmd2->arr_cmd = arr_cmd2;
	cmd2->path = find_path(paths, cmd2->arr_cmd);
	cmd2->env = env;
	cmd2->fd_in = -1;
	cmd2->fd_out = -1;
	cmd2->redirs = NULL;
	cmd2->indx = 2;
	cmd2->next = NULL;

	cmds->next = cmd2;*/

/*	cmd3 = malloc(sizeof(t_cmd) * 1);
	if (!cmd3)
		return (NULL);
	arr_cmd3 = malloc(sizeof(char *) * 2);
	if (!arr_cmd3)
		return (NULL);
	arr_cmd3[0] = malloc(sizeof(char) * (ft_strlen(argv[5]) + 1));
	if (!arr_cmd3[0])
		return (NULL);
	ft_strlcpy(arr_cmd3[0], argv[5], (ft_strlen(argv[5]) + 1));
	arr_cmd3[1] = NULL;
	cmd3->arr_cmd = arr_cmd3;
	cmd3->path = find_path(paths, cmd3->arr_cmd);
	cmd3->env = env;
	cmd3->fd_in = -1;
	cmd3->fd_out = -1;
	cmd3->redirs = NULL;
	cmd3->indx = 3;
	cmd3->next = NULL;

	cmd2->next = cmd3;*/

/*	cmd4 = malloc(sizeof(t_cmd) * 1);
	if (!cmd4)
		return (NULL);
	arr_cmd4 = malloc(sizeof(char *) * 2);
	if (!arr_cmd4)
		return (NULL);
	arr_cmd4[0] = malloc(sizeof(char) * (ft_strlen(argv[7]) + 1));
	if (!arr_cmd4[0])
		return (NULL);
	ft_strlcpy(arr_cmd4[0], argv[7], (ft_strlen(argv[7]) + 1));
	arr_cmd4[1] = NULL;
	cmd4->arr_cmd = arr_cmd4;
	cmd4->path = find_path(paths, cmd4->arr_cmd);
	cmd4->env = env;
	cmd4->fd_in = -1;
	cmd4->fd_out = -1;
	cmd4->redirs = NULL;
	cmd4->indx = 4;
	cmd4->next = NULL;*/

/*	cmd4->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd4->redirs)
		return (NULL);
	cmd4->redirs->type = HEREDOC;
	cmd4->redirs->file_name = argv[11];
	cmd4->redirs->fd = -1;
	cmd4->redirs->next = NULL;*/
	
/*	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->type = OUTPUT;
	tmp->file_name = argv[11];
	tmp->fd = -1;
	tmp->next = NULL;

	cmd4->redirs->next = tmp;*/

//	cmd3->next = cmd4;

//	print_cmds(cmds);
//	print_redirs_lst(cmds->redirs);
	return (cmds);
}

int	executor(t_cmd *segmts, t_info *info)
{
	t_cmd	*aux;
	t_exec	exec_info;

	if (!segmts)
		return (-1);
	if (set_exec_info(info->envp, &exec_info) == 1) // todos los posibles paths, or_fds, etc
		return (-1);
	aux = segmts;
	find_heredocs(segmts);
	if (!segmts->next)
	{
		exec_simp_cmd(segmts, info, &exec_info);
		//reseteo STD_IN y STD_OUT
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
		printf("%d en cmd con pid %d\n", WEXITSTATUS(info->ex_stat), aux->pid);
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
