/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 13:31:23 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/01 12:44:17 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "libft/libft.h"
/*
static size_t	ft_strlen(char *s)
{
	size_t	e;

	e = 0;
	while (s[e] != '\0')
		e++;
	return (e);
}
*/

void	exit_free(char *str, int i, t_info *info)
{
	write(1, str, ft_strlen(str));
	if (i == 1)
	{
		free_envlst(info->envp);
	}
	if (i == 2)
	{
		free_envlst(info->envp);
		if (info->tokens != NULL)
			free_lexlst(info->tokens);
	}
}

int valid_line(t_info *info)
{
	int i;

	i = 0;
	while (info->rl[i])
	{
		if (info->rl[i] == '"')
		{
			i++;
			while(info->rl[i] != '"' && info->rl[i] != '\0')
				i++;
			if(info->rl[i] == '\0')
				{
					exit_free("Doble quotes are not closed\n", 1, info);
					return(0);
				}
		}
		if (info->rl[i] == 39)
		{
			i++;
			while (info->rl[i] != 39 && info->rl[i] != '\0')
				i++;
			if(info->rl[i] == '\0')
			{
				exit_free("Single quotes aren't closed\n", 1, info);
				return(0);
			}
		}
		if(info->rl[i])
			i++;
		if (info->rl[i] =='\0')
			return (1);
	}
	return (1);
}
/*
int main()
{
	char *str;
	
	while (1)
	{
		str = readline("Prompt >");
		valid_line(str);
		free(str);
	}
	rl_clear_history();
	return (0);
}*/


