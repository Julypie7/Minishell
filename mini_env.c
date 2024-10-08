/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:41:11 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/07 11:46:56 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "builtin.h"
#include "struct.h"

int	mini_env(char **argv, t_info *info)
{
	t_envp	*tmp;

	tmp = info->envp;
	if (argv[1])
	{
		printf("env: '%s': No such file or directory\n", argv[1]);
		return (1);
	}
	while (tmp)
	{
		printf("%s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
