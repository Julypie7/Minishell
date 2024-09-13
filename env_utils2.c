/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 21:51:04 by martalop          #+#    #+#             */
/*   Updated: 2024/09/09 20:47:02 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

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

char	**free_array(char **array) // CAMBIAR A RETURN VOID
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
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
	int	i;
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
