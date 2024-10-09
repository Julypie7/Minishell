/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:04:40 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/09 12:48:00 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	copy_env(t_info *info, t_envp *env)
{
	t_envp	*new_env;
	t_envp	*first;

	new_env = NULL;
	first = env;
	return (copy_process(first, new_env, info));
}

int	copy_process(t_envp *first, t_envp *new_env, t_info *info)
{
	while (first)
	{
		new_env = malloc(sizeof(t_envp) * 1);
		if (!new_env)
		{
			write(2, "malloc error copy of env_list\n", 30);
			return (2);
		}
		new_env->key = ft_strdup(first->key);
		if (!new_env->key)
		{
			free(new_env);
			return (2);
		}
		new_env->value = ft_strdup(first->value);
		if (!new_env->value)
		{
			free(new_env->key);
			return (2);
		}
		new_env->next = NULL;
		add_node_to_env(&info->copy, new_env);
		first = first->next;
	}
	return (0);
}

int	mini_export(char **argv, t_info	*info)
{
	int	i;
	int	len;
	int	flag;

	i = 1;
	flag = 0;
	len = how_much(argv, info);
	if (len == 0)
		return (0);
	len = check_of_arg(argv, len, info);
	if (len == -1)
		return (1);
	if (!info->copy)
	{
		if (copy_env(info, info->envp) == 2)
			return (2);
	}
	while (argv[i])
	{
		flag = check_keys(info, argv[i]);
		if (flag == 1)
			flag = not_in_env(info, argv[i]);
		i++;
	}
	return (flag);
}
