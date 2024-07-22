/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:25:10 by martalop          #+#    #+#             */
/*   Updated: 2024/07/22 14:56:50 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

//int	find_arr_len(); TO DO

int	find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (0);
	return (i);
}

void	env_to_list(t_info *info, char **env)
{
	int		found_at;
	int			i;
	t_envp		*node;

	i = 0;
//	i = find_arr_len(env); TO DO

	while (env[i])
	{
		node = malloc(sizeof(t_envp) * 1);
		if (!node)
		{
			write(2, "malloc error at env copy creation\n", 34);
			exit(1);
		}
		// variable name
		found_at = find_equal(env[i]);
		node->key = ft_substr(env[i], 0, found_at + 1);
		// content of variable
		node->value = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		node->next = NULL;
		add_node_to_env(&info->envp, node);
		i++;
	}
}

void	print_env(t_envp **lst)
{
	int	i;

	i = 0;
	while (*lst)
	{
		printf("env[%d]:\nKEY: %s\nVALUE: %s\n\n", i, (*lst)->key, (*lst)->value);
		*lst = (*lst)->next;
		i++;
	}
}

void	add_node_to_env(t_envp **lst, t_envp *node)
{
	t_envp	*tmp;

	if(!(*lst))
	{
		(*lst) = node;
	}
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

