/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:51:04 by martalop          #+#    #+#             */
/*   Updated: 2024/09/17 20:25:00 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	fill_env_node(char *env_line, t_envp *node, t_envp **env_lst)
{
	int	found_at;

	found_at = 0;
	found_at = find_equal(env_line);
	node->key = ft_substr(env_line, 0, found_at + 1);
	if (!node->key)
	{
		free_envlst(*env_lst);
		return (1);
	}
	node->value = ft_substr(env_line, found_at + 1,
			ft_strlen(env_line) - found_at);
	if (!node->value)
	{
		free(node->key);
		free_envlst(*env_lst);
		return (1);
	}
	node->next = NULL;
	return (0);
}

void	free_envlst(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		tmp = tmp->next;
		free(envp->key);
		free(envp->value);
		free(envp);
		envp = tmp;
	}
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_char_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	print_env(t_envp *lst)
{
	int		i;
	t_envp	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		printf("env[%d]:\nKEY: %s\nVALUE: %s\n\n", i, tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
}
