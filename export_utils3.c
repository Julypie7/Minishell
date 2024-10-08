/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:24:08 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/08 18:37:22 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	not_in_env(t_info *info, char *export)
{
	t_envp	*tmp;
	int		i;

	tmp = info->copy;
	i = find_equal(export);
	if (i)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, export) == 0)
			{
				if (check_change_copy(info->copy, export, i) == 2)
					return (2);
				i = change_copy_equal(export, info->envp, i);
				return (i);
			}
			tmp = tmp->next;
		}
		if (add_node_to_copy(info, info->copy, export) == 2)
			return (2);
		i = add_node_to_copy(info, info->envp, export);
		return (i);
	}
	else
		return (add_node_to_copy(info, info->copy, export));
}

int	add_node_to_copy(t_info *info, t_envp *env, char *export)
{
	t_envp	*new;
	t_envp	*tmp;
	int		i;
	
	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	i = find_equal(export);
	if (i)
	{
		if (add_node_ch_val(tmp, i, export) == 2)
			return (2);
	}
	else
	{
		if (add_node_without_val(tmp, 0, export) == 2)
			return (2);
	}
	return (0);
}

int	check_change_copy(t_envp *copy, char *export, int i)
{
	t_envp	*tmp;
	t_envp	*last;
	int		e;

	tmp = copy;
	while (tmp)
	{
		e = find_equal(tmp->key);
		if (!e)
		{
			if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key) == 0))
				return (copy_without_equal(tmp, export, i, e));
		}
		else
			if (ft_strncmp(tmp->key, export, i) == 0)
				return (copy_with_eq(tmp, export, i));
		tmp = tmp->next;
	}
	return (1);
}

void	print_env_sorted(t_info *info)
{
	t_envp	*sorted;

	sorted = sort_alg(info->copy, NULL);
	info->copy = sorted;
	while (sorted)
	{
		if (sorted->key[0] == '_' && sorted->key[2])
		{
			printf("declare -x %s\"%s\"\n", sorted->key, sorted->value);
			sorted = sorted->next;
		}
		else if (sorted->key[0] == '_' && !sorted->key[2])
			sorted = sorted->next;
		else
		{
			printf("declare -x %s", sorted->key);
			if (sorted->value != NULL && sorted->value[0] != '\0')
				printf("\"%s\"", sorted->value);
			printf("\n");
			sorted = sorted->next;
		}
	}
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
