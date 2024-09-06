/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:16:53 by martalop          #+#    #+#             */
/*   Updated: 2024/09/05 22:38:09 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "parsing.h"

int	simple_syntax(t_lex_lst *tokens)
{
	t_lex_lst	*tkn;
	int			i;
	int			word;

	i = 0;
	word = 0;
	tkn = tokens;
	while (tkn)
	{
		if (!tkn->word)
		{
			if (tkn->type == PIPE && word == 0)
			{
				write(2, "syntax error near unexpected token\n", 35);
				return (1);
			}
			if (!tkn->next || !tkn->next->word || !tkn->next->word[0])
			{
				write(2, "syntax error near unexpected token\n", 35);
				return (1);
			}
			i++;
		}
		else
			word = 1;
		tkn = tkn->next;
	}
	if (i > 16)
	{
		write(2, "maximum heredoc limit exceeded(16)\n", 35);
		return (1);
	}
	return (0);
}
