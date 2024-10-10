/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:31:23 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 19:26:42 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft/libft.h"

void	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
}

void	exit_free(char *str, int i, t_info *info)
{
	write(2, str, ft_strlen(str));
	if (i == 1)
	{
		free_envlst(info->envp);
	}
	if (i == 2)
	{
		free_envlst(info->envp);
		if (info->tokens != NULL)
			free_lexlst(info->tokens);
		exit (1);
	}
}

int	valid_line(t_info *info)
{
	int	i;

	i = 0;
	while (info->rl[i])
	{
		if (info->rl[i] == '"' || info->rl[i] == 39)
		{
			i++;
			while ((info->rl[i] != '"' || info->rl[i] != 39) \
					&& info->rl[i] != '\0')
				i++;
			if (info->rl[i] == '\0')
				return (error_msg("Quotes are not closed\n"), 0);
		}
		if (info->rl[i])
			i++;
		if (info->rl[i] == '\0')
			return (1);
	}
	return (1);
}

int	handle_quotes(t_info *info, int i)
{
	int	j;

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
