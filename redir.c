/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:37 by martalop          #+#    #+#             */
/*   Updated: 2024/08/04 14:29:44 by martalop         ###   ########.fr       */
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
// -> fork necesario
// -> redireccion (dup2) en el padre

// ------     ./a.out      "<"        infile     cat     ------
// ------     argv[0]   argv[1]     argv[2]    argv[3]  ------

int	open_redir(char **argv)
{
	int	fd;

//	print_char_arr(argv);
	fd = open(argv[2], O_RDONLY);
	if (fd == -1)
		perror("cannot open redirection");
//	printf("%d\n", fd);
	return (fd);
}

int	redirect(int fd)
{
	if (dup2(fd, 0) == -1)
	{
		write(2, "dup2 failed\n", 12);
		return (1);
	}
	close(fd);
	return (0);
}

t_cmd_info	*set_cmd(char **argv, char **env, t_info *info)
{
	t_cmd_info	*cmd;
	char	**arr_cmd;
	char	*path;
	
	cmd = malloc(sizeof(t_cmd_info) * 1);
	if (!cmd)
		return (NULL);
	arr_cmd = malloc(sizeof(char *) * 2);
	if (!arr_cmd)
		return (NULL);
	arr_cmd[0] = argv[3];
	arr_cmd[1] = NULL;
	cmd->arr_cmd = arr_cmd;
	cmd->path = "/usr/bin/cat";
	cmd->env = env;
	cmd->pid = 0;
	return (cmd);
}

int	execute(t_cmd_info *cmd, t_info *info)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (1);
	if (cmd->pid == 0)
	{
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

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	int		fd;
	char	**new_env;
	t_cmd_info	*cmd;

	info.ex_stat = 0;
	fd = open_redir(argv);
	if (fd == -1)
		return (1);

	if (redirect(fd) == 1)
		return (1);

//	new_env = envlst_to_arr() -> tendre que hacer esto prq en la struct info me llega como lista
	cmd = set_cmd(argv, env, &info);
	execute(cmd, &info);
	waitpid(cmd->pid, &(info.ex_stat), 0);
	close(fd);
	return (WEXITSTATUS(info.ex_stat));
}
