/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:38:27 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/07 10:38:48 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

t_envp	*do_unset(t_info *info, t_envp *to_unset)
{
	t_envp	*prev;
	t_envp	*current;

	prev = NULL;
	current = info->envp;
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
		info->envp = current->next;
	free(current);
	return (info->envp);
}

int	mini_unset(char **argv, t_info *info)
{
	t_envp	*current;
	int		i;

	i = 1;
	while (argv[i])
	{
		current = info->envp;
		while (current)
		{
			if (ft_strncmp(current->key, argv[i], \
						(ft_strlen(current->key) - 1)) == 0)
			{
				info->envp = do_unset(info, current);
				current = info->envp;
			}
			else
				current = current->next;
		}
		i++;
	}
	return (0);
}
