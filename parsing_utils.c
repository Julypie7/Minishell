/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:49:30 by martalop          #+#    #+#             */
/*   Updated: 2024/10/05 21:54:52 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"
#include "parsing.h"

int	classify_tkn(t_lex_lst **tokens, t_cmd **aux_cmd)
{
	if ((*tokens)->type == INPUT || (*tokens)->type == OUTPUT
		|| (*tokens)->type == HEREDOC || (*tokens)->type == APPEND)
	{
		if (add_redir(*tokens, *aux_cmd) == 2)
			return (0);
		*tokens = (*tokens)->next;
	}
	else if ((*tokens)->word)
	{
		(*aux_cmd)->arr_cmd = add_to_array((*tokens)->word,
				(*aux_cmd)->arr_cmd);
		if (!(*aux_cmd)->arr_cmd)
			return (0);
	}
	else if ((*tokens)->type == PIPE)
	{
		(*aux_cmd)->next = create_cmd_node();
		if (!(*aux_cmd)->next)
			return (0);
		*aux_cmd = (*aux_cmd)->next;
	}
	return (1);
}

char	**create_arr_cmd(char *word, char **arr_cmd)
{
	arr_cmd = malloc(sizeof(char *) * 2);
	if (!arr_cmd)
		return (NULL);
	arr_cmd[0] = ft_strdup(word);
	if (!arr_cmd[0])
		return (NULL);
	arr_cmd[1] = NULL;
	return (arr_cmd);
}

int	add_first_rdir(t_lex_lst *tokens, t_cmd *cmd)
{
	int	filename_len;

	filename_len = ft_strlen(tokens->next->word);
	cmd->redirs = malloc(sizeof(t_redir) * 1);
	if (!cmd->redirs)
		return (0);
	cmd->redirs->type = tokens->type;
	cmd->redirs->file_name = malloc(sizeof(char) * (filename_len + 1));
	if (!cmd->redirs->file_name)
		return (0);
	ft_strlcpy(cmd->redirs->file_name, tokens->next->word, (filename_len + 1));
	cmd->redirs->fd = -1;
	cmd->redirs->amb_red = 0;
	cmd->redirs->next = NULL;
	return (1);
}

int	add_rest_rdirs(t_lex_lst *tokens, t_cmd *cmd)
{
	t_redir	*tmp;
	int		filename_len;

	filename_len = ft_strlen(tokens->next->word);
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_redir) * 1);
	if (!tmp->next)
		return (0);
	tmp->next->type = tokens->type;
	tmp->next->file_name = malloc(sizeof(char) * (filename_len + 1));
	if (!tmp->next->file_name)
		return (0);
	ft_strlcpy(tmp->next->file_name, tokens->next->word, (filename_len + 1));
	tmp->next->fd = -1;
	tmp->next->amb_red = 0;
	tmp->next->next = NULL;
	return (1);
}
