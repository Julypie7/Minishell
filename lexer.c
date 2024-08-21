/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <ineimatu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:16:16 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/06 14:48:19 by ineimatu         ###   ########.fr       */
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
	int j;
	
	j = 0;
	while (avoid(line[i + j]))
		j++;
	return (j);
}

int handle_quotes(t_info *info, int i)
{
	int j;

	j = 1;
	if (info->rl[i] == 39)
	{
		while (info->rl[i + j] != 39)
			j++;
		return (++j);
	}
	else if (info->rl[i] == 34)
	{
		while (info->rl[i + j] != 34)
			j++;
		return (++j);
	}
	return (0);
}
	
int check_inside(t_info *info, int i)
{
	int j;

	j = 0;
	if (info->rl[i] == 39)
	{
		while (info->rl[++i] != 39)
			i++;
		while (info->rl[i] != 39)
		{
			if (info->rl[i] >= 33 && info->rl[i] <= 126)
			   j++;
			i--;
		}
		if (j > 0)
			return (1);
		else
			return (0);
	}
	else
	{
		while (info->rl[++i] != 34)
			i++;
		while (info->rl[i] != 34)
		{
			if (info->rl[i] >= 33 && info->rl[i] <= 126)
			   j++;
			i--;
		}
		if (j > 0)
			return (1);
		else
			return (0);
	}
}
				
int word(t_info *info, int i)
{
	int j;

	j = 0;
	if (info->rl[i + j] == 39 || info->rl[i + j] == 34)
	{
			/*if (!check_inside(info, i))
			{
				j = handle_quotes(info, i);
				return (j);
			}
			if (check_inside(info, i))
			{*/
		j = handle_quotes(info, i);
		if (!add_node(ft_substr(info->rl, i, j), NULL, info))
			return (-1);
		return (j);
	}
	while (info->rl[i + j] && info->rl[j + i] != ' ')
	{
		if (avoid(info->rl[i + j]))
			return (j);
		else
			j++;
	}
	if (!add_node(ft_substr(info->rl, i, j), NULL, info))
		return (-1);
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
