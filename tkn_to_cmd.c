/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:36:23 by martalop          #+#    #+#             */
/*   Updated: 2024/09/24 18:44:58 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "parsing.h"
#include "libft/libft.h"

t_cmd	*create_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd) * 1);
	if (!cmd)
		return (NULL);
	cmd->arr_cmd = NULL;
	cmd->path = NULL;
	cmd->pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

int	add_redir(t_lex_lst *tokens, t_cmd *cmd)
{
	if (!cmd->redirs)
	{
		if (!add_first_rdir(tokens, cmd))
			return (2);
	}
	else
	{
		if (!add_rest_rdirs(tokens, cmd))
			return (2);
	}
	return (1);
}

int	find_arr_size(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

char	**add_to_array(char *word, char **arr_cmd)
{
	int		i;
	char	**new_array;

	i = 0;
	new_array = NULL;
	if (!arr_cmd)
		return (create_arr_cmd(word, arr_cmd));
	new_array = malloc(sizeof(char *) * (find_arr_size(arr_cmd) + 2));
	if (!new_array)
		return (NULL);
	while (arr_cmd[i])
	{
		new_array[i] = arr_cmd[i];
		i++;
	}
	new_array[i] = ft_strdup(word);
	if (!new_array[i])
		return (NULL);
	new_array[++i] = NULL;
	free(arr_cmd);
	return (new_array);
}

t_cmd	*tkn_to_cmd(t_lex_lst *tokens)
{
	t_cmd	*cmd;
	t_cmd	*aux_cmd;

	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	aux_cmd = cmd;
	while (tokens)
	{
		if (!classify_tkn(&tokens, &aux_cmd))
		{
			free_cmds(cmd);
			return (NULL);
		}
		tokens = tokens->next;
	}
	return (cmd);
}

/*int	main(void)
{
	t_cmd	*cmd;
	t_lex_lst	*tokens;
	t_lex_lst	*tokens2;
	t_lex_lst	*tokens3;
	t_lex_lst	*tokens4;
	t_lex_lst	*tokens5;
	t_lex_lst	*tokens6;
	t_lex_lst	*tokens7;
	t_lex_lst	*tokens8;
	t_lex_lst	*tokens9;
	t_lex_lst	*tokens10;
	t_lex_lst	*tokens11;

	cmd = NULL;

	tokens = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens)
		return (1);
	tokens->word = NULL;
	tokens->type = INPUT;
	tokens->t_content = "<";
	tokens->next = NULL;

	tokens2 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens2)
		return (1);
		return (1);
	tokens->word = NULL;
	tokens->type = INPUT;
	tokens->t_content = "<";
	tokens->next = NULL;

	tokens2 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens2)
		return (1);
	tokens2->word = "infile";
	tokens2->type = -1;
	tokens2->t_content = NULL;
	tokens2->next = NULL;

	tokens->next = tokens2;

	tokens3 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens3)
		return (1);
	tokens3->word = "cat";
	tokens3->type = -1;
	tokens3->t_content = NULL;
	tokens3->next = NULL;

	tokens2->next = tokens3;

	tokens4 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens4)
		return (1);
	tokens4->word = NULL;
	tokens4->type = OUTPUT;
	tokens4->t_content = ">";
	tokens4->next = NULL;

	tokens3->next = tokens4;

	tokens5 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens5)
		return (1);
	tokens5->word = "outfile";
	tokens5->type = -1;
	tokens5->t_content = NULL;
	tokens5->next = NULL;

	tokens4->next = tokens5;

	tokens6 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens6)
		return (1);
	tokens6->word = "-e";
	tokens6->type = -1;
	tokens6->t_content = NULL;
	tokens6->next = NULL;

	tokens5->next = tokens6;
	
	tokens7 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens7)
		return (1);
	tokens7->word = NULL;
	tokens7->type = PIPE;
	tokens7->t_content = "|";
	tokens7->next = NULL;

	tokens6->next = tokens7;

	tokens8 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens8)
		return (1);
	tokens8->word = "ls";
	tokens8->type = -1;
	tokens8->t_content = NULL;
	tokens8->next = NULL;

	tokens7->next = tokens8;

	tokens9 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens9)
		return (1);
	tokens9->word = NULL;
	tokens9->type = OUTPUT;
	tokens9->t_content = ">";
	tokens9->next = NULL;

	tokens8->next = tokens9;

	tokens10 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens10)
		return (1);
	tokens10->word = "out";
	tokens10->type = -1;
	tokens10->t_content = NULL;
	tokens10->next = NULL;

	tokens9->next = tokens10;

	tokens11 = malloc(sizeof(t_lex_lst) * 1);
	if (!tokens11)
		return (1);
	tokens11->word = "-a";
	tokens11->type = -1;
	tokens11->t_content = NULL;
	tokens11->next = NULL;

	tokens10->next = tokens11;

	print_lex_lst(tokens);
	
	cmd = tkn_to_cmd(tokens);
	print_cmds(cmd);
	free_lexlst(tokens);
	free_cmds(cmd);
	return (0);
}*/
