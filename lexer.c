/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:16:16 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/24 13:53:28 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
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

int lexer(t_info *info)
{
	int i;
	
	i = 0;
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

