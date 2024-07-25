/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:22:37 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/25 17:25:40 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(t_info *info, int i)
{
	int j;
	int count;
	char *tmp;

	j = i;
	count = 0;
	i++;
	while (info->rl[i] && (info->rl[i + 1] != 34 || info->rl[i + 1] != 39))
		i++;
	count = i - j;
	tmp = (char *)malloc(sizeof(char) * count);
	if (!tmp)
		return (0);
	i = ++j;
	j = 0;
	while (j <= count)
	{
		tmp[j] = info->rl[i + j];
		j++;
	}
	tmp[j] = '\0';
	add_node(tmp, NULL, 1, info->tokens);
	return (j - 1);
}

int	word(t_info *info, int i)
{
	char *tmp;
	int	j;

	j = 0;
	while (info->rl[i + j] != " ")
	   j++;
	tmp = (char *)malloc(sizeof(char) * j);
	if (!tmp)
		return (0);
	j = 0;
	while (info->rl[i + j] != " ")
	{
		tmp[j] = info->rl[i + j];
		j++;
	}
	tmp[j] = '\0';
	add_node(tmp, NULL, 0, info->tokens);
	return (j - 1);
}


