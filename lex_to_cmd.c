/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:36:23 by martalop          #+#    #+#             */
/*   Updated: 2024/09/06 20:26:48 by martalop         ###   ########.fr       */
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
	// array de comando (para luego)
	cmd->arr_cmd = NULL;
	// path del comando (para luego)
	// lista de redirs (para luego)
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
		cmd->redirs->file_name = tokens->next->word; // cuidado los frees
	}
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next =  malloc(sizeof(t_redir) * 1);
		if (!tmp->next)
			return (2);
		tmp->next->token = tokens->type;
		tmp->next->file_name = tokens->next->word;
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

t_cmd	*lex_to_cmd(t_lex_lst *tokens)
{
	t_cmd	*cmd;
	t_lex_lst	*aux;

	aux = tokens;
	cmd = create_cmd_node();
	if (!cmd)
		return (NULL);
	while (tokens)
	{
		if (tokens->type == INPUT || tokens->type == OUTPUT || tokens->type == HEREDOC || tokens->type == APPEND)
		{
			add_redir(tokens, cmd);
			tokens = tokens->next;
		}
		else if (tokens->word)
		{
			cmd->arr_cmd = add_to_array(tokens->word, cmd->arr_cmd);
			if (!cmd->arr_cmd)
				return (NULL);
		}
	/*	else if (tokens->type == PIPE)
		{
			// crear siguiente cmd
			// conectarlo al next del anterior comando
		}*/
		tokens = tokens->next;
	}
	return (cmd);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*aux;

	aux = cmds;
	while (aux)
	{
		printf("CMD[%p]\narr_cmd: %p\npath: %s\npid : %d\nfd_in: %d, fd_out: %d\nredirs: %p\nindex: %d\n\n", aux, aux->arr_cmd, aux->path, aux->pid, aux->fd_in, aux->fd_out, aux->redirs, aux->indx);
		if (aux->arr_cmd)
			printf("arr_cmd[0]: %s, arr_cmd[1]: %s, arr_cmd[2]: %s\n\n", aux->arr_cmd[0], aux->arr_cmd[1], aux->arr_cmd[2]);
		aux = aux->next;
	}
}

void	print_redirs_lst(t_redir *redirs)
{
	t_redir	*tmp;

	tmp = redirs;
	while (tmp)
	{
		printf("redir[%p]\ntoken: %d\nfile_name: %s\nfd: %d\n\n", tmp, tmp->token, tmp->file_name, tmp->fd);
		tmp = tmp->next;
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

	cmd = malloc(sizeof(t_cmd) * 1);
	cmd->arr_cmd = NULL;
	cmd->path = NULL;
	cmd->env = NULL;
	cmd->pid = -1;
	cmd->fd_in = -1;
	cmd->fd_out = -1;
	cmd->redirs = NULL;
	cmd->indx = 1;
	cmd->next = NULL;

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
	
//	print_lex_lst(tokens);

//	add_redir(tokens, cmd);
	
	print_cmds(cmd);
	cmd = lex_to_cmd(tokens);
	print_cmds(cmd);
	print_redirs_lst(cmd->redirs);
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
