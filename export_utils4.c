/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:50:29 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/09 13:01:13 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	add_node_ch_val(t_envp *tmp, int i, char *export)
{
	t_envp	*new;
	
	new = malloc(sizeof(t_envp));
	if (!new)
		return (2);
	new->key = ft_substr(export, 0, i + 1);
	if (!new->key)
	{
		free(new);
		return (2);
	}
	new->value = ft_substr(export, ft_strlen(new->key), ft_strlen(export) - i);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return(2);
	}
	new->next = NULL;
	tmp->next = new;
	return (0);
}

int	add_node_without_val(t_envp *tmp, int i, char *export)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (2);
	new->key = ft_substr(export, 0, ft_strlen(export));
	if (!new->key)
	{
		free(new);
		return (2);
	}
	new->value = malloc(sizeof(char));
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (2);
	}
	new->value[0] = '\0';
	new->next = NULL;
	tmp->next = new;
	return (0);
}

int	copy_without_equal(t_envp *tmp, char *export, int i, int q)
{
	free(tmp->key);
	free(tmp->value);
	tmp->key = ft_substr(export, 0, i + 1);
	printf("%s\n", tmp->key);
	if (export[ft_strlen(tmp->key)] != 0)
		tmp->value = ft_substr(export, i, ft_strlen(export) - i);
	else
	{
		tmp->value = malloc(sizeof(char));
		if (!tmp->value)
			return (2);
		tmp->value[0] = '\0';
	}
	return (0);
}

int	copy_with_eq(t_envp *tmp, char *export, int i)
{
	free(tmp->value);
	if (export[ft_strlen(tmp->key)] != 0)
		tmp->value = ft_substr(export, ft_strlen(tmp->key), ft_strlen(export) - i);
	else
	{
		tmp->value = malloc(sizeof(char));
		if (!tmp->value)
			return (2);
		tmp->value[0] = '\0';
	}
	return (0);
}

int	exists_in_env(t_envp *env, char *export)
{
	t_envp	*tmp;


	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, export, ft_strlen(tmp->key)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
