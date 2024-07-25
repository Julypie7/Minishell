/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:32:50 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/25 17:15:03 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_list	new_node(char *str, char *token, int q, t_info *info)
{
	t_lex_list *new_node;
	static int	i = 0;

	new_node = malloc(sizeof(t_lex_list) * 1);
	if (!new_node)
		exit_free("malloc err of new node lexer\n", 2, info);
	new_node->word = str;
	new_node->quotes = q;
	if (token == ">")
		new_node->type = OUTPUT;
	if (token == ">>")
		new_node->type = APPEND;
	if (token == "<")
		new_node->type = INPUT;
	if (token == "<<")
		new_node->type = HEREDOC;
	if (token == "|")
		new_node->type = PIPE;
	new_node->t_content = token;
	new_node->elem = i++;
	new_node->next = NULL;
	return (new_node);
}

void	add_new_node(t_lex_list *node, t_lex_list **tokens)
{
	t_lex_list	tmp;

	tmp = *tokens;
	if (*tokens == NULL)
	{
		*tokens = node;
		return;
	}
	while(tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

int	add_node(char *str, char *token, t_info *info)
{
	t_lex_list	*node;

	node = new_node(str, token, info);
	if (!node)
		return (0);
	add_new_node(node, info->tokens);
	return (1);
}
