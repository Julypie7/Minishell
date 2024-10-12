/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitin_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:53:34 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 11:40:58 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

void	free_pwd(char *pwd)
{
	printf("cd: error retrieving current directory");
	free(pwd);
}

int	exists_in_copy(t_envp *env, char *export)
{
	t_envp	*tmp;

	tmp = env;
	if (find_equal(export))
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
				return (1);
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (ft_strncmp(tmp->key, export, ft_strlen(export)) == 0)
				return (1);
			tmp = tmp->next;
		}
	}
	return (0);
}

t_envp	*sort_alg(t_envp *lst_export, t_envp *sorted)
{
	t_envp	*current;
	t_envp	*the_next;
	t_envp	*tmp;

	current = lst_export;
	while (current)
	{
		the_next = current->next;
		if (!sorted || ft_strcmp(current->key, sorted->key) < 0)
		{
			current->next = sorted;
			sorted = current;
		}
		else
		{
			tmp = sorted;
			while (tmp->next && ft_strcmp(current->key,
					tmp->next->key) >= 0)
				tmp = tmp->next;
			current->next = tmp->next;
			tmp->next = current;
		}
		current = the_next;
	}
	return (sorted);
}
