/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:38:27 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 10:56:33 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

t_envp	*do_unset(t_envp *list, t_envp *to_unset)
{
	t_envp	*prev;
	t_envp	*current;

	prev = NULL;
	current = list;
	while (current->key != to_unset->key)
	{
		prev = current;
		current = current->next;
	}
	free(current->key);
	free(current->value);
	if (prev)
		prev->next = current->next;
	if (!prev)
		list = current->next;
	free(current);
	return (list);
}

void	check_unset_copy(t_envp *copy, char *argv)
{
	t_envp	*current;

	current = copy;
	while (current)
	{
		if (ft_strncmp(current->key, argv, \
						(ft_strlen(current->key) - 1)) == 0)
		{
			copy = do_unset(copy, current);
			current = copy;
			return ;
		}
		else
			current = current->next;
	}
}

int	mini_unset(char **argv, t_info *info)
{
	t_envp	*current;
	int		i;

	i = 1;
	while (argv[i])
	{
		current = info->envp;
		if (info->copy)
			check_unset_copy(info->copy, argv[i]);
		while (current)
		{
			if (ft_strncmp(current->key, argv[i], \
						(ft_strlen(current->key) - 1)) == 0)
			{
				info->envp = do_unset(info->envp, current);
				current = info->envp;
			}
			else
				current = current->next;
		}
		i++;
	}
	return (0);
}
