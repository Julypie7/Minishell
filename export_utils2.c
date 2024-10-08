/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:21:34 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/08 17:56:18 by ineimatu         ###   ########.fr       */
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

	i = 0;
	tmp = info->envp;
	flag = 1;
	while (tmp)
	{
		if ((ft_strncmp(tmp->key, export, ft_strlen(tmp->key) - 1) == 0) \
			&& (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) != 0))
			flag = 2;
		if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
			flag = 1;
		tmp = tmp->next;
	}
	tmp = info->envp;
	if (flag == 2)
		return (0);
	/*if (check_change_copy(copy, export) == 0)
		return(0);*/
	if (flag == 1)
		return (equal(export, i, tmp, info));
	else
		return (1);
}

int	equal(char *export, int i, t_envp *tmp, t_info *info)
{
	while (tmp)
	{
		if (find_equal(export))
		{
			if (ft_strncmp(export, tmp->key, find_equal(export)) == 0)
			{
				if (change_copy_equal(export, info->copy, i) == 2)
					return (2);
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
		if (ft_strncmp(export, tmp->key, find_equal(export)) == 0)
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
	return (1);
}
