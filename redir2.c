/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:37 by martalop          #+#    #+#             */
/*   Updated: 2024/09/02 20:47:19 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "struct.h"

// ejemplo de un COMANDO SUELTO con REDIRECCIONES (hardcoded, sin buscar path y haciendo el char ** malamente)
// -> fork necesario prq hacemos execve para ejecutar el comando
// -> redireccion (dup2) en el padre

// -----   ./a.out      "<"       infile     "<<"        lim        cat       ">>"      out      ">"      out2    ------
// -----   argv[0]   argv[1]     argv[2]   argv[3]    argv[4]     argv[5]   argv[6]  argv[7]  argv[8]   argv[9]  ------

int	heredoc(char *lim)
{
	char	*str;
	int		pipe_here[2];

	str = NULL;
	if (pipe(pipe_here) == -1)
		return (write(2, "pipe failed\n", 12), -1);
	while (1)
	{
		// leo de terminal
		str = readline("> ");
		// si la linea leida de terminal es = a limiter, cierro el fd de escritura y paro el bucle de lectura
		if (!ft_strncmp(str, lim, ft_strlen(lim) + 1))
		{
			free(str);
			close(pipe_here[1]);
			break ;
		}
		// si la linea leida NO es = limiter, guardo la linea en el fd de escritura de la pipe y sigo leyendo
		write(pipe_here[1], str, ft_strlen(str));
		write(pipe_here[1], "\n", 1);
		free(str);
	}
	return (pipe_here[0]);

}

int	open_redir(t_redir *redirs)
{
	while (redirs)
	{
//		fprintf(stderr, "%d\n", redirs->token);
		if (redirs->token == INPUT)
		{
		//	write(2, "open con input\n", 15); 
			redirs->fd = open(redirs->file_name, O_RDONLY);
			if (redirs->fd == -1)
			{
				perror(redirs->file_name);
				return (1);
			}
		}
/*		else if (redirs->token == HEREDOC)
		{
		//	write(2, "open con heredoc\n", 17); 
			redirs->fd = heredoc(redirs->file_name); // heredoc devuelve el fd de lectura de la pipe del documento heredoc
											 // file_name es el limiter
			if (redirs->fd == -1)
				return (1);
		}*/
		else if (redirs->token == APPEND)
		{
		//	write(2, "open con append\n", 16);
			redirs->fd = open(redirs->file_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
			if (redirs->fd == -1)
			{
				perror(redirs->file_name);
				return (1);
			}
		}
		else if (redirs->token == OUTPUT)
		{
		//	write(2, "open con output\n", 16);
			redirs->fd = open(redirs->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redirs->fd == -1)
			{
				perror(redirs->file_name);
				return (1);
			}
		}
		redirs = redirs->next;
	}
	return (0);
}

int	redirect(t_redir *redirs)
{
	while (redirs)
	{
		if (redirs->token == INPUT || redirs->token == HEREDOC)
		{
			if (dup2(redirs->fd, 0) == -1)
			{
				write(2, "dup2 failed\n", 12);
				return (1);
			}
		}
		else if (redirs->token == OUTPUT || redirs->token == APPEND)
		{
			if (dup2(redirs->fd, 1) == -1)
			{
				write(2, "dup2 failed\n", 12);
				return (1);
			}
		}
		close(redirs->fd); // no se si es necesario
		redirs = redirs->next;
	}
	return (0);
}

int	count_cmds(char *rl)
{
	int	i;
	int	pipes;

	i = 0;
	pipes = 0;
	while (rl && rl[i])
	{
		if (rl[i] == '|')
			pipes++;
		i++;
	}
	if (pipes != 0)
		pipes++;
	return (pipes);
}

t_cmd	*set_cmd(char **argv, char **env, t_info *info, t_exec *exec_info)
{
	t_cmd	*cmd;
	t_redir	*tmp;
	t_redir	*tmp2;
	t_redir	*tmp3;
	
	exec_info->paths = prep_cmd_paths(env);
	if (!exec_info->paths)
		return (write(2, "problem splitting paths\n", 24), NULL);
	exec_info->or_fd[0] = dup(0);
	exec_info->or_fd[1] = dup(1);
//	exec_info->cmd_num = count_cmds(info->rl);
	exec_info->cmd_num = 1;
	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->arr_cmd = malloc(sizeof(char *) * 2);
	if (!cmd->arr_cmd)
		return (NULL);
	cmd->arr_cmd[0] = argv[5];
	cmd->arr_cmd[1] = NULL;
	cmd->path = find_path(exec_info->paths, cmd->arr_cmd);
	if (!cmd->path)
		return (write(2, "problem finfing path\n", 21), NULL);
	cmd->env = env;
//	cmd->env = envlst_to_arr() -> tendre que hacer esto prq en la struct info me llega como lista
	cmd->pid = 0;

	//  REDIRS LIST
	cmd->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd->redirs)
		return (NULL);
	cmd->redirs->token = INPUT;
	cmd->redirs->file_name = argv[2];
	cmd->redirs->fd = -1;
	cmd->redirs->next = NULL;
	
	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->token = HEREDOC;
	tmp->file_name = argv[4];
	tmp->fd = -1;
	tmp->next = NULL;

	cmd->redirs->next = tmp;
	
	tmp2 = malloc(sizeof(t_redir) * 1);
	if (!tmp2)
		return (NULL);
	tmp2->token = APPEND;
	tmp2->file_name = argv[7];
	tmp2->fd = -1;
	tmp2->next = NULL;

	tmp->next = tmp2;

	tmp3 = malloc(sizeof(t_redir) * 1);
	if (!tmp3)
		return (NULL);
	tmp3->token = OUTPUT;
	tmp3->file_name = argv[9];
	tmp3->fd = -1;
	tmp3->next = NULL;

	tmp2->next = tmp3;

	cmd->indx = 1;
	cmd->next = NULL;
	return (cmd);
}

void	remove_fds(t_redir *redirs)
{
/*	int	i;

	i = 0;
	while (i < 2 - 1) // num de redirecciones menos 1 para que no pille la última
	{
		close(fd[i]);
		i++;
	}*/
	int		i;
	int		j;
	t_redir	*tmp;

	i = 0;
	j = 0;
	tmp = redirs;
	while (tmp)
	{
		if (tmp && (tmp->token == INPUT || tmp->token == HEREDOC) && i < 2 - 1)
		{
			write(2, "close de input fd\n", 18);
			close(tmp->fd);
			i++;
		}
		else if (tmp->token == OUTPUT && j < 1 - 1)
		{
			write(2, "close de output fd\n", 19);
			close(tmp->fd);
			j++;
		}
		tmp = tmp->next;
	}
}

int	execute(t_cmd *cmd, t_info *info)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		if (open_redir(cmd->redirs) == 1)
			return (1);
//		remove_fds(cmd->redirs);
		redirect(cmd->redirs);

		if (execve(cmd->path, cmd->arr_cmd, cmd->env) == -1)
		{
			write(2, "execve failed\n", 14);
			info->ex_stat = 1;
			exit(1);
		}
	}
	return (0);
}

// si execve tiene el path de 'cat' pero un char ** de 'ls' como argumento, por qué no falla??
	// -> parece ser que sustituye el primer argumento del array con el path que le mandemos
	// -> por tanto si el path es correcto, da igual cual sea el argumento, que lo ejecutará bien

/*int	main(int argc, char **argv, char **env)
{
	t_info	info;
	t_exec	exec_info;
	t_cmd	*cmd;

	info.ex_stat = 0;
	cmd = set_cmd(argv, env, &info, &exec_info);
	if (!cmd)
		return (1);
//	print_redirs_lst(cmd->redirs);
	if (execute(cmd, &info) == 1)
		return (1);
	waitpid(cmd->pid, &(info.ex_stat), 0);
	return (WEXITSTATUS(info.ex_stat));
}*/
