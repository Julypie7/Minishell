/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:16:53 by martalop          #+#    #+#             */
/*   Updated: 2024/10/12 22:36:29 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "parsing.h"

int	handle_tkn_syntax(t_lex_lst *tokens, int *here_count, int *word)
{
	if (tokens->type == PIPE && *word == 0)
	{
		write(2, "syntax error near unexpected token\n", 35);
		return (1);
	}
	if (!tokens->next || (tokens->type != PIPE && (!tokens->next->word
				|| !tokens->next->word[0])))
	{
		write(2, "syntax error near unexpected token\n", 35);
		return (1);
	}
	if (tokens->type == HEREDOC)
		*here_count = *here_count + 1;
	return (0);
}

int	simple_syntax(t_lex_lst *tokens)
{
	int	here_count;
	int	word;

	here_count = 0;
	word = 0;
	while (tokens)
	{
		if (!tokens->word)
		{
			if (handle_tkn_syntax(tokens, &here_count, &word) == 1)
				return (2);
		}
		else
			word = 1;
		tokens = tokens->next;
	}
	if (here_count > 16)
	{
		write(2, "maximum heredoc limit exceeded(16)\n", 35);
		return (2);
	}
	return (0);
}
