/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:21:34 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 11:11:44 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	check_keys(t_info *info, char *export)
{
	t_envp	*tmp;
	int		i;
	int		flag;

	i = find_equal(export);
	tmp = info->envp;
	flag = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
			flag = 1;
		tmp = tmp->next;
	}
	tmp = info->envp;
	if (flag == 1)
		return (equal(export, i, tmp, info));
	else
		return (1);
}

int	equal(char *export, int i, t_envp *tmp, t_info *info)
{
	tmp = info->envp;
	while (tmp)
	{
		if (find_equal(export))
		{
			if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
			{
				i = ft_strlen(export) - ft_strlen(tmp->key);
				free(tmp->value);
				if (export[ft_strlen(tmp->key)] != 0)
					tmp->value = ft_substr(export, ft_strlen(tmp->key), i);
				else
				{
					tmp->value = malloc(sizeof(char));
					if (!tmp->value)
						return (2);
					tmp->value[0] = '\0';
				}
				return (change_copy_equal(export, info->copy, i));
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	change_copy_equal(char *export, t_envp *copy, int i)
{
	t_envp	*tmp;

	tmp = copy;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
		{
			i = ft_strlen(export) - ft_strlen(tmp->key);
			free(tmp->value);
			if (export[ft_strlen(tmp->key)] != 0)
				tmp->value = ft_substr(export, ft_strlen(tmp->key), i);
			else
			{
				tmp->value = malloc(sizeof(char));
				if (!tmp->value)
					return (2);
				tmp->value[0] = '\0';
			}
			return (0);
		}
		tmp = tmp->next;
	}
	tmp = copy;
	return (1);
}
