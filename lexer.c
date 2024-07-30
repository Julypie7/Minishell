/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:16:16 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/30 14:29:49 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	avoid(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (1);
	return (0);
}

int	ign_spaces(char *line, int i)
{
	int j;
	
	j = 0;
	while (avoid(line[i + j]))
		j++;
	return (j);
}

int word(t_info *info, int i)
{
	int j;

	j = 0;
	while (info->rl[i + j] && info->rl[j + i] != ' ')
	{
		if (info->rl[i + j] == 39)
			j = handle_quotes(info, i);
		else if (info->rl[i + j] == 34)
			j = handle_quotes(info, i);
		else
			j = handle_word(info, i);
	}
	return (j);
}

int lexer(t_info *info)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (info->rl[i])
	{
		i += ign_spaces(info->rl, i);
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
