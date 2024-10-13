/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:51:30 by martalop          #+#    #+#             */
/*   Updated: 2024/10/10 22:35:42 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execution.h"
#include "libft/libft.h"

char	*check_cmd_access(char **paths, char *cmd)
{
	int		x;
	char	*tmp;

	x = 0;
	while (paths[x])
	{
		tmp = ft_strjoin(paths[x], cmd);
		if (!tmp)
			return (NULL);
		if (!access(tmp, X_OK))
			return (tmp);
		free(tmp);
		x++;
	}
	tmp = ft_strdup(cmd);
	return (tmp);
}

char	*find_path(char **paths, char **arr_cmd)
{
	int		x;
	char	*tmp;

	x = 0;
	if (!arr_cmd || arr_cmd[0] == NULL)
	{
		tmp = ft_strdup("");
		return (tmp);
	}
	if (arr_cmd[0][0] == '/')
	{
		tmp = ft_strdup(arr_cmd[0]);
		return (tmp);
	}
	if (arr_cmd[0][0] == '.' && arr_cmd[0][1] == '/')
	{
		tmp = ft_strdup(arr_cmd[0]);
		return (tmp);
	}
	tmp = check_cmd_access(paths, arr_cmd[0]);
	return (tmp);
}

char	**create_empty_array(void)
{
	char	**arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("");
	if (!arr[0])
		return (NULL);
	arr[1] = NULL;
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
