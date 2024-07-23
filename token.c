/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:33:28 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/23 13:00:44 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishel.h"
#include "lexer.h"

int	token_exist(char token, t_lex_lst *tokens)
{
	if (token == '|')
	{
		if (!add_node(NULL, PIPE, tokens));
			return (exit_free("err w pipe node", 1));
		return (1);
	}
	if (token == '>')
		return (1);
	if (token == '<')
		return (1);
}

int	second_check(char *line, int i, t_lex_lst *tokens)
{
	if (line[i] == '>' && line[i + 1] == '>')
	{
		if(!add_node(NULL, APPEND, tokens))
			return(exit_free("err w append node", 1));
		return (2);
	}
	if (line[i] == '<' && line[i + 1] == '<')
	{
		if(!add_node(NULL, HEREDOC, tokens))
			return(exit_free("err w heredoc node", 1));
		return (2);
	}
}

int	check_token(char *line, int i, t_lex_lst *tokens)
{
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (second_check(line, &i, tokens));
		else (!add_node(NULL, OUTPUT, tokens))
			return(exit_free("err w out node", 1));
		return (1);
	}
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (second_check(line, &i, tokens));
		else (!add_node(NULL, INPUT, tokens));
			return(exit_free("err w inp node", 1));
		return(1);
	}
	else if (line[i] == '|')
		return (1);
}


