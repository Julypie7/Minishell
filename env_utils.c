/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:25:10 by martalop          #+#    #+#             */
/*   Updated: 2024/07/22 21:56:04 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

int	envlst_size(t_envp *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->next != NULL)
		{
			lst = lst->next;
			i++;
		}
		else
		{
			i++;
			break ;
		}
	}
	return (i);
}

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
	while (env[i])
	{
		node = malloc(sizeof(t_envp) * 1);
		if (!node)
		{
			write(2, "malloc error at env copy creation\n", 34);
			free_envlst(info->envp);
			exit(1);
		}
		// variable name
		found_at = find_equal(env[i]);
		node->key = ft_substr(env[i], 0, found_at + 1);
		if (!node->key)
		{
			free_envlst(info->envp);
			exit (1);
		}
		// content of variable
		node->value = ft_substr(env[i], found_at + 1, ft_strlen(env[i]) - found_at);
		if (!node->value)
		{
			free(node->key);
			free_envlst(info->envp);
			exit (1);
		}
		node->next = NULL;
		add_node_to_env(&info->envp, node);
		i++;
	}
}
char	**envlst_to_arr(t_envp *envp)
{
	int		i;
	t_envp	*tmp;
	char	**arr;
	int		key_len;
	int		val_len;

	i = 0;
	tmp = envp;
	arr = malloc(sizeof(char *) * (envlst_size(envp) + 1));
	if (!arr)
		return (NULL);
	while (tmp)
	{
		key_len = ft_strlen(tmp->key);
		val_len = ft_strlen(tmp->value);
		arr[i] = malloc(sizeof(char) * (key_len + val_len + 1));
		if (!arr[i])
			return (free_array(arr));
		ft_strlcpy(arr[i], tmp->key, (key_len + 1));
		ft_strlcpy(&arr[i][key_len], tmp->value, (val_len + 1));
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
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
