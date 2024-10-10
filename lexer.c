/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:16:16 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 19:13:19 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft/libft.h"

int	avoid(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ign_spaces(char *line, int i)
{
	int	j;

	j = 0;
	while (line && avoid(line[i + j]))
		j++;
	return (j);
}

int	word(t_info *info, int i)
{
	int	j;

	j = 0;
	if (info->rl[i + j] == 39 || info->rl[i + j] == 34)
	{
		j = handle_quotes(info, i);
		if (!add_node(ft_substr(info->rl, i, j), NULL, info))
			return (-1);
		return (j);
	}
	while (info->rl[i + j] && info->rl[j + i] != ' ' \
			&& !token_exist(info->rl[i + j]))
	{
		if (info->rl[i + j] == 39 || info->rl[i + j] == 34)
			j += handle_quotes(info, j + i);
		else if (avoid(info->rl[i + j]))
			return (j);
		else
			j++;
	}
	if (!add_node(ft_substr(info->rl, i, j), NULL, info))
		return (-1);
	return (j);
}

int	zero_case(t_info *info, int i)
{
	int	n;

	n = 0;
	while (info->rl[i])
	{
		if (info->rl[i] == ' ' && (!info->rl[i + 1] || info->rl[i + 1] == ' '))
			if (i == 0 || info->rl[i - 1] == ' ')
				n++;
		i++;
	}
	if (i == n)
		return (1);
	return (0);
}

int	lexer(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (zero_case(info, i))
		return (0);
	while (info->rl[i])
	{
		i += ign_spaces(info->rl, i);
		if (!info->rl[i])
			return (1);
		if (token_exist(info->rl[i]))
			j = check_token(info, i);
		else
			j = word(info, i);
		if (j < 0)
			return (0);
		i += j;
	}
	return (1);
}
