/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:36:23 by martalop          #+#    #+#             */
/*   Updated: 2024/10/12 22:56:22 by martalop         ###   ########.fr       */
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
		return (free_array(arr_cmd), NULL);
	while (arr_cmd[i])
	{
		new_array[i] = arr_cmd[i];
		i++;
	}
	new_array[i] = ft_strdup(word);
	if (!new_array[i])
		return (free_array(arr_cmd), free(new_array), NULL);
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
