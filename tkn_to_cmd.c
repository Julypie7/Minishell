/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkn_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:36:23 by martalop          #+#    #+#             */
/*   Updated: 2024/09/08 20:30:37 by martalop         ###   ########.fr       */
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
	cmd->env = NULL;
	cmd->pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->redirs = NULL;
	cmd->indx = 1;
	cmd->next = NULL;
	return (cmd);
}

int	add_redir(t_lex_lst *tokens, t_cmd *cmd)
{
	t_redir	*tmp;

	if (!cmd->redirs)
	{	
		cmd->redirs = malloc(sizeof(t_redir) * 1);
		if (!cmd->redirs)
			return (2);
		cmd->redirs->token = tokens->type;
		cmd->redirs->file_name = malloc(sizeof(char) * (ft_strlen(tokens->next->word) + 1)); // cuidado los frees
		if (!cmd->redirs->file_name)
			return (2);
		ft_strlcpy(cmd->redirs->file_name, tokens->next->word, (ft_strlen(tokens->next->word) + 1));
		cmd->redirs->fd = -1;
		cmd->redirs->next = NULL;
	}
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_redir) * 1);
		if (!tmp->next)
			return (2);
		tmp->next->token = tokens->type;
		tmp->next->file_name = malloc(sizeof(char) * (ft_strlen(tokens->next->word) + 1));
		if (!tmp->next->file_name)
			return (2);
		ft_strlcpy(tmp->next->file_name, tokens->next->word, (ft_strlen(tokens->next->word) + 1));
		tmp->next->fd = -1;
		tmp->next->next = NULL;
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
	int	i;
	char	**new_array;

	i = 0;
	if (!arr_cmd)
	{
		arr_cmd = malloc(sizeof(char *) * 2);
		if (!arr_cmd)
			return (NULL);
		arr_cmd[0] = malloc(sizeof(char) * (ft_strlen(word) + 1));
		if (!arr_cmd[0])
			return (NULL);
		ft_strlcpy(arr_cmd[0], word, (ft_strlen(word) + 1));
	//	free(word); // si luego libero todos los lex_lst tokens esto me daria doble free?
		arr_cmd[1] = NULL;
		return (arr_cmd);
	}
	new_array = malloc(sizeof(char *) * (find_arr_size(arr_cmd) + 2));
	if (!new_array)
		return (NULL);
	while (arr_cmd[i])
	{
		new_array[i] = malloc(sizeof(char) * (ft_strlen(arr_cmd[i]) + 1));
		if (!new_array[i])
			return (NULL);
		ft_strlcpy(new_array[i], arr_cmd[i], (ft_strlen(arr_cmd[i]) + 1));
		i++;
	}
	new_array[i] = malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!new_array[i])
		return (NULL);
	ft_strlcpy(new_array[i], word, (ft_strlen(word) + 1));
	i++;
//	free(word); // si luego libero todos los lex_lst tokens esto me daria doble free?
	new_array[i] = NULL;
	free_array(arr_cmd);
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
		if (tokens->type == INPUT || tokens->type == OUTPUT || tokens->type == HEREDOC || tokens->type == APPEND)
		{
			if (add_redir(tokens, aux_cmd) == 2)
			{
				write(2, "add_redir failed\n", 17);
				return (NULL);
			}
			tokens = tokens->next;
		}
		else if (tokens->word)
		{
			aux_cmd->arr_cmd = add_to_array(tokens->word, aux_cmd->arr_cmd);
			if (!aux_cmd->arr_cmd)
				return (NULL);
		}
		else if (tokens->type == PIPE)
		{
			aux_cmd->next = create_cmd_node();
			if (!aux_cmd->next)
				return (NULL);
			aux_cmd = aux_cmd->next;
		}
		tokens = tokens->next;
	}
	return (cmd);
}

void	print_redirs_lst(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		printf("redir[%p]\ntoken: %d\nfile_name: %s\nfd: %d\nnext: %p\n\n", tmp, tmp->token, tmp->file_name, tmp->fd, tmp->next);
		tmp = tmp->next;
	}
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*aux;
	int		i;

	aux = cmds;
	while (aux)
	{
		printf("CMD[%p]\narr_cmd: %p\npath: %s\npid : %d\nfd_in: %d, fd_out: %d\nredirs: %p\nindex: %d\nnext: %p\n", aux, aux->arr_cmd, aux->path, aux->pid, aux->fd_in, aux->fd_out, aux->redirs, aux->indx, aux->next);
		i = 0;
		while (aux->arr_cmd[i])
		{
			printf("arr_cmd[%d]: %s\n", i, aux->arr_cmd[i]);
			i++;
		}
		print_redirs_lst(aux->redirs);
		write(2, "\n", 1);
		aux = aux->next;
	}
}

void	free_redir_lst(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		tmp = tmp->next;
		free(redirs->file_name);
		free(redirs);
		redirs = tmp;
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		tmp = tmp->next;
		free_array(cmds->arr_cmd);
	//	free(cmds->path);
	//	free_array(env);
		if (cmds->redirs)
			free_redir_lst(cmds->redirs);
		free(cmds);
		cmds = tmp;
	}
}

int	main(void)
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
}

/*int	main(void)
{
	char	*str;
	char	*str2;
	char	*str3;
	char	**arr;
	int		i;

	i = 0;
	str = "hola";
	arr = add_to_array(str, NULL);
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	write(2, "\n", 1);
	str2 = malloc(sizeof(char) * 5);
	str2[0] = 'c';
	str2[1] = 'h';
	str2[2] = 'a';
	str2[3] = 'o';
	str2[4] = '\0';
	arr = add_to_array(str2, arr);
	i = 0;
	free(str2);
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	write(2, "\n", 1);
	str3 = malloc(sizeof(char) * 5);
	str3[0] = 't';
	str3[1] = 'e';
	str3[2] = 's';
	str3[3] = 't';
	str3[4] = '\0';
	arr = add_to_array(str3, arr);
	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
	write(2, "\n", 1);
	free(str3);
	free_array(arr);
	return (0);
}*/
