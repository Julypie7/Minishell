/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:33:28 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/21 14:13:02 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	token_exist(char token)
{
	if (token == '|' || token == '>' || token == '<')
		return (1);
	return (0);
}

int	second_check(t_info *info, int i)
{
	if (info->rl[i] == '>' && info->rl[i + 1] == '>')
	{
		if(!add_node(NULL, ">>", info))
		{
			exit_free("err w append node", 2, info);
			return (-1);
		}
		return (2);
	}	
	else if (info->rl[i] == '<' && info->rl[i + 1] == '<')
	{
		if(!add_node(NULL, "<<", info))
		{
			exit_free("err w heredoc node", 2, info);
			return (-1);
		}
		return (2);
	}
	return (1);
}

int	check_token(t_info *info, int i)
{
	if (info->rl[i] == '>')
	{
		if (info->rl[i + 1] == '>')
			return (second_check(info, i));
		else 
		{
			if (!add_node(NULL, ">", info))
			{
				exit_free("err w out node", 2, info);
				return (-1);
			}
		}
		return (1);
	}
	else if (info->rl[i] == '<')
	{
		if (info->rl[i + 1] == '<')
			return (second_check(info, i));
		else
		{	
			if (!add_node(NULL, "<", info))
			{
				exit_free("err w inp node", 2, info);
				return (-1);
			}
		}
		return(1);
	}
	else 
	{
	/*	if (i == 0)
		{
			error_msg("Syntax error\n");
			return (-1);
		}
		*/
		if (!add_node(NULL, "|", info))
		{
			exit_free("err w pipe node", 2, info);
			return (-1);
		}
		return (1);
	}
}
