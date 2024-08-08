/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:37 by martalop          #+#    #+#             */
/*   Updated: 2024/08/08 22:40:01 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// ejemplo de un COMANDO SUELTO con REDIRECCIONES (hardcoded, sin buscar path y haciendo el char ** malamente)
// -> fork necesario prq hacemos execve para ejecutar el comando
// -> redireccion (dup2) en el padre

// ------     ./a.out      "<"       infile     "<"      outfile       cat       ">"      out     ------
// ------     argv[0]   argv[1]     argv[2]   argv[3]    argv[4]     argv[5]   argv[6]  argv[7]   ------

int	open_redir(t_redir *redirs)
{
//	if (redirs && (redirs->token == INPUT || redirs->token == HEREDOC))
//	{
	while (redirs)
	{
		if (redirs && (redirs->token == INPUT || redirs->token == HEREDOC))
		{
			write(2, "entra en input\n", 15);
			redirs->fd = open(redirs->file_name, O_RDONLY);
			if (redirs->fd == -1)
			{
				write(2, redirs->file_name, ft_strlen(redirs->file_name));
				write(2, ": ", 2);
				perror("");
				return (1);
			}
		}
		else if (redirs->token == OUTPUT)
		{
			write(2, "entra en outout\n", 16);
			redirs->fd = open(redirs->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (redirs->fd == -1)
			{
				write(2, redirs->file_name, ft_strlen(redirs->file_name));
				write(2, ": ", 2);
				perror("");
				return (1);
			}
		}
		redirs = redirs->next;
	}
//	}
//	else if (redirs && redirs->token == OUTPUT)
//	{
//		while (redirs)
//		{
//			redirs->fd = open(redirs->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//			if (redirs->fd == -1)
//			{
//				write(2, redirs->file_name, ft_strlen(redirs->file_name));
//				write(2, ": ", 2);
//				perror("");
//				return (1);
//			}
//			redirs = redirs->next;
//		}
//	}
	return (0);
}

int	redirect(t_redir *redirs)
{
	while (redirs->next)
		redirs = redirs->next;
	if (redirs->token == INPUT || redirs->token == HEREDOC)
	{
		if (dup2(redirs->fd, 0) == -1)
		{
			write(2, "dup2 failed\n", 12);
			return (1);
		}
	}
	else if (redirs->token == OUTPUT)
	{
		if (dup2(redirs->fd, 1) == -1)
		{
			write(2, "dup2 failed\n", 12);
			return (1);
		}
	}
	close(redirs->fd);
	
	
	/*while (redirs)
	{
		if (!(redirs->next))
		{
			redirs
			if (redirs && (redirs->token == INPUT || redirs->token == HEREDOC))
			{
				if (dup2(redirs->fd, 0) == -1)
				{
					write(2, "dup2 failed\n", 12);
					return (1);
				}
			}
			else if (redirs && redirs->token == OUTPUT)
			{
				if (dup2(redirs->fd, 1) == -1)
				{
					write(2, "dup2 failed\n", 12);
					return (1);
				}
			}
			close(redirs->fd);
		}
		redirs = redirs->next;
	}*/

/*	redirs = cmd->out_redirs;
	if (redirs && redirs->token == OUTPUT)
	{
		while (redirs)
		{
			if (!(redirs->next))
			{
				if (dup2(redirs->fd, 1) == -1)
				{
					write(2, "dup2 failed\n", 12);
					return (1);
				}
				close(redirs->fd);
			}
			redirs = redirs->next;
		}
	}*/
	return (0);
}

t_cmd	*set_cmd(char **argv, char **env, t_info *info)
{
	t_cmd	*cmd;
	char	**arr_cmd;
	char	*path;
	t_redir	*tmp;
	
	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	arr_cmd = malloc(sizeof(char *) * 2);
	if (!arr_cmd)
		return (NULL);
	arr_cmd[0] = argv[5];
//	arr_cmd[1] = "infile";
//	arr_cmd[2] = "holabola";
	arr_cmd[2] = NULL;
	cmd->arr_cmd = arr_cmd;
	cmd->path = "/usr/bin/cat";
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
	
	cmd->redirs->next = tmp;
	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->token = INPUT;
	tmp->file_name = argv[4];
	tmp->fd = -1;
	tmp->next = NULL;

	cmd->redirs->next = tmp;
	
	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->token = OUTPUT;
	tmp->file_name = argv[7];
	tmp->fd = -1;
	tmp->next = NULL;

	cmd->redirs->next = tmp;


/*	//OUT REDIRS LIST 
	cmd->out_redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd->out_redirs)
		return (NULL);
	cmd->out_redirs->token = OUTPUT;
	cmd->out_redirs->file_name = argv[7];
	cmd->out_redirs->fd = -1;
	cmd->out_redirs-> next = NULL;*/
	
/*	tmp = malloc(sizeof(t_redir) * 1);
	if (!tmp)
		return (NULL);
	tmp->token = 0;
	tmp->file_name = NULL;
	tmp->fd = -1;
	tmp->next = NULL;
	
	cmd->out_redirs->next = tmp;*/
	
	cmd->indx = 1;
	cmd->next = NULL;
	return (cmd);
}

int	execute(t_cmd *cmd, t_info *info)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
		open_redir(cmd->redirs);
	//	remove_fds();
	
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

void	remove_fds(int	*fd)
{
	int	i;

	i = 0;
	while (i < 2 - 1) // num de redirecciones menos 1 para que no pille la última
	{
		close(fd[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	int		*fd;
	char	**new_env;
	t_cmd	*cmd;

	info.ex_stat = 0;
	cmd = set_cmd(argv, env, &info);
	execute(cmd, &info); // FORK & EXECVE
	waitpid(cmd->pid, &(info.ex_stat), 0);
	return (WEXITSTATUS(info.ex_stat));
}
