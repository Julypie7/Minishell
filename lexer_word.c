/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:22:37 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/30 14:58:38 by ineimatu         ###   ########.fr       */
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
		return (-1);
	i = ++j;
	j = 0;
	while (j < count)
	{
		tmp[j] = info->rl[i + j];
		j++;
	}
	tmp[j] = '\0';
	if (!add_node(tmp, NULL, 1, info))
		return (-1);
	return (j);
}

int	handle_word(t_info *info, int i)
{
	char *tmp;
	int	j;

	j = 0;
	while (info->rl[i + j] != ' ' || info->rl[i + j] != '\0')
	   j++;
	tmp = (char *)malloc(sizeof(char) * j);
	if (!tmp)
		return (-1);
	j = 0;
	while (info->rl[i + j] != ' ')
	{
		tmp[j] = info->rl[i + j];
		j++;
	}
	tmp[j] = '\0';
	if (!add_node(tmp, NULL, 0, info))
		return (-1);
	return (j - 1);
}
