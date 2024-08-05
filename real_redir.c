/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:54:10 by martalop          #+#    #+#             */
/*   Updated: 2024/08/04 17:56:48 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"
#include "execution.h"

void	add_node_to_lex_list(t_lex_lst **lst, t_lex_lst *node)
{
	t_lex_lst	*tmp;

	if(!(*lst))
	{
		(*lst) = node;
	}
	else
	{
		tmp = (*lst);
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

// ---- cat < infile1 < infile2 > outfile ----

t_lex_lst	*create_token_list(void)
{
	t_lex_lst	*first_node;
	t_lex_lst	*node;

	first_node = malloc(sizeof(t_lex_lst) * 1);
	if (!first_node)
		return (NULL);
	first_node->word = malloc(sizeof(char) * 4);
	first_node->word = ft_strlcpy(first_node->word, "cat", 3);
	first_node->type = 0; // not a redirection
	first_node->t_content = NULL;
	first_node->file = 0;
	first_node->next = NULL;
	
	node = malloc(sizeof(t_lex_lst) * 1);
	if (!node)
		return (NULL);
	node->word = NULL;
	node->type = INPUT;
	node->t_content = malloc(sizeof(char) * 2);
	node->t_content = ft_strlcpy(node->t_content, "<", 1);
	node->file = 0;
	node->next = NULL;

	add_node_to_lex_list(&first_node, node);
	
	node = malloc(sizeof(t_lex_lst) * 1);
	if (!node)
		return (NULL);
	node->word = malloc(sizeof(char) * 8);
	node->word = ft_strlcpy(node->word, "infile1", 7);
	node->type = 0;
	node->t_content = NULL;
	node->file = 1;
	node->next = NULL;


}

int	main(int argc, char **argv, char **env)
{
	t_lex_lst	*elem_list;
	
	elem_list =	create_token_list();
	if (redirect()== 1 )
		return (1);
	return (0);
}
