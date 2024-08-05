/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:51:30 by martalop          #+#    #+#             */
/*   Updated: 2024/07/30 13:31:53 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "execution.h"
#include "minishell.h"
#include "libft/libft.h"

// 						 < infile grep hola > outfile

// hacer que mi programa acepte 1 comando con 2 redirecciones (probar no solo con cat)

char	**create_arr(void)
{
	char	**cmd_arr;
	char	*cmd_s;
	char	*arg;
	int		arg_of_cmd;
	int		i;
	
	i = 0;
	cmd_s = "grep";
	arg = "hola";
	arg_of_cmd = 2; // cmd + su argumento
	cmd_arr = malloc(sizeof(char *) * (arg_of_cmd + 1));
	while (i < arg_of_cmd)
	{
		if (i == 0)
		{
			cmd_arr[i] = malloc(sizeof(char) * (ft_strlen(cmd_s) + 1));
			ft_strlcpy(cmd_arr[i], cmd_s, (ft_strlen(cmd_s) + 1));
		}
		else
		{
			cmd_arr[i] = malloc(sizeof(char) * (ft_strlen(arg) + 1));
			ft_strlcpy(cmd_arr[i], arg, (ft_strlen(arg) + 1));
		}
		i++;
	}
	cmd_arr[i] = NULL;
	return (cmd_arr);
}

char	**create_empty_array(void)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 1);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("");
	if (!arr[0])
		return (NULL);
	return (arr);
}

char	**join_for_path(char **paths)
{
	int		x;
	char	*tmp;

	x = 0;
	while (paths[x])
	{
		tmp = ft_strjoin(paths[x], "/");
		if (!tmp)
			return (free_array(paths), NULL);
		free(paths[x]);
		paths[x] = tmp;
		x++;
	}
	return (paths);
}

char	**prep_cmd_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (env[i] && !ft_strnstr(env[i], "PATH", 4))
		i++;
	if (!env[i])
	{
		paths = create_empty_array();
		if (!paths)
			return (NULL);
		return (paths);
	}
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	paths = join_for_path(paths);
	if (!paths)
		return (NULL);
	return (paths);
}

t_cmd	*set_command(char **paths)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (perror("bad malloc in set_command"), NULL);
	cmd->arr_cmd = create_arr();
	if (!cmd->arr_cmd)
	{
		free(cmd);
		return (perror("problem spliting argument"), NULL);
	}
	print_char_arr(cmd->arr_cmd);
	return (cmd);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_info	info;
	t_cmd	*cmd;
	char	**paths;
	
	//preparar info basica de comando y env
	paths = prep_cmd_paths(env);
	cmd = set_command(paths);
	//redirecciones
	
	//comandos	
/*	cmd->path = find_path(paths, cmd->arr_cmd);
	if (!cmd->path)
	{
		free_array(cmd->arr_cmd);
		free(cmd);
		perror("problem creating cmd path");
		return (NULL);
	} */
}
