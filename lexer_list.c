/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:32:50 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/02 13:13:03 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
void	print_lex_lst(t_lex_lst *node)
{
	t_lex_lst	*tmp;

	tmp = node;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%p\nword: %d\ntype: %d\nt_content: %s\nelem: %d\nnext: %p\n\n", node, node->word, node->type, node->t_content, node->elem, node->next);
		tmp = tmp->next;
	}
}*/

t_lex_lst	*new_node(char *str, char *token, t_info *info)
{
	t_lex_lst *new_node;
	static int	i = 0;

	new_node = malloc(sizeof(t_lex_lst) * 1);
	if (!new_node)
	{
		exit_free("malloc err of new node lexer\n", 2, info);
		exit (1);
	}
	new_node->word = str;
	if (token && token[0])
	{
		if (token[0] == '>')
			new_node->type = OUTPUT;
		if (token[1] == '>')
			new_node->type = APPEND;
		if (token[0] == '<')
			new_node->type = INPUT;
		if (token[1] == '<')
			new_node->type = HEREDOC;
		if (token[0] == '|')
			new_node->type = PIPE;
	}
	new_node->t_content = token;
	new_node->elem = i++;
	new_node->next = NULL;
	return (new_node);
}

void	add_new_node(t_lex_lst *node, t_lex_lst **tokens)
{
	t_lex_lst	*tmp;

	tmp = *tokens;
	if (*tokens == NULL)
	{
		*tokens = node;
		return;
	}
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = node;
}

int	add_node(char *str, char *token, t_info *info)
{
	t_lex_lst	*node;
	
	node = NULL;
	node = new_node(str, token, info);
	if (!node)
		return (0);
//	printf("token: %p\n", info->tokens);
	add_new_node(node, &(info->tokens));
//	print_lex_lst(node);
	return (1);
}

void	free_lexlst(t_lex_lst *tokens)
{
	t_lex_lst	*tmp;

	tmp = tokens;
	while (tmp)
	{
		tmp = tmp->next;
		free(tokens->word);
		//free(tokens->t_content);
		free(tokens);
		tokens = tmp;
	}
}
