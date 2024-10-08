/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:34:31 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/07 10:34:34 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

void	change_pwd(t_envp *lst)
{
	t_envp	*tmp;
	char	*swop;

	tmp = lst;
	swop = getcwd(NULL, 0);
	while (lst)
	{
		if (ft_strcmp(lst->key, "PWD=") == 0)
		{
			free(lst->value);
			lst->value = malloc(sizeof(char) * (ft_strlen(swop) + 1));
			lst->value = ft_strcpy(lst->value, swop);
			lst = lst->next;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	free(swop);
}

int	check_var_exist(char *path, t_info *info)
{
	if (path[0] == '-' || path[0] == '~')
		path = ft_getenv("HOME=", info->envp);
	if (chdir(path) == -1)
	{
		if (path == ft_getenv("HOME=", info->envp))
			printf("cd: HOME not set\n");
		else
			printf("cd: %s: NO such file or directory\n", path);
		return (1);
	}
	else
		return (0);
}

int	just_cd(t_envp *lst, char *path, t_info *info)
{
	t_envp	*tmp;
	char	*pwd;

	tmp = lst;
	pwd = getcwd(NULL, 0);
	if (check_var_exist(path, info) == 1)
		return (1);
	change_pwd(tmp);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, "OLDPWD=") == 0)
		{
			free(tmp->value);
			tmp->value = malloc(sizeof(char) * (ft_strlen(pwd) + 1));
			if (!tmp->value)
				return (2);
			tmp->value = ft_strcpy(tmp->value, pwd);
			break ;
		}
		else
			tmp = tmp->next;
	}
	return (free(pwd), 0);
}

int	count_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
		return (1);
	return (0);
}

int	mini_cd(char **argv, t_info *info)
{
	char	*home;

	home = ft_getenv("HOME=", info->envp);
	if (count_arg(argv) == 1)
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	else if (argv[0] && !argv[1])
		return (just_cd(info->envp, home, info));
	else
		return (just_cd(info->envp, argv[1], info));
}
