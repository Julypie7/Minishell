/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:33:28 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/24 13:53:24 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
#include "lexer.h"

int	token_exist(char token)
{
	if (token == '|' || token == '>' || token == '<')
		return (1);
}

int	second_check(t_info *info, int i)
{
	if (info->rl[i] == '>' && info->rl[i + 1] == '>')
	{
		if(!add_node(NULL, ">>", info->tokens))
			return(exit_free("err w append node", 2, info));
		return (2);
	}
	if (info->rl[i] == '<' && info->rl[i + 1] == '<')
	{
		if(!add_node(NULL, "<<", info->tokens))
			return(exit_free("err w heredoc node", 2, info));
		return (2);
	}
}

int	check_token(t_info *info, int i)
{
	if (info->rl[i] == '>')
	{
		if (info->rl[i + 1] == '>')
			return (second_check(info, &i));
		else (!add_node(NULL, ">", info->tokens))
			return(exit_free("err w out node", 2, info));
		return (1);
	}
	else if (info->rl[i] == '<')
	{
		if (info->rl[i + 1] == '<')
			return (second_check(info, &i));
		else (!add_node(NULL, "<", info->tokens));
			return(exit_free("err w inp node", 2, info));
		return(1);
	}
	else if (info->rl[i] == '|')
	{
		if (i == 0)
			return (exit_free("syntax er<<<ror", 1));
		if (!add_node(NULL, "|", info->tokens));
			return (exit_free("err w pipe node", 2, info));
		return (1);
	}
}


