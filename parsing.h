/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:54:35 by martalop          #+#    #+#             */
/*   Updated: 2024/10/04 14:11:41 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "struct.h"
# include "minishell.h"
# include "libft/libft.h"

int		classify_tkn(t_lex_lst **tokens, t_cmd **aux_cmd);
t_cmd	*create_cmd_node(void);
char	**add_to_array(char *word, char **arr_cmd);
int		add_redir(t_lex_lst *tokens, t_cmd *cmd);
int		simple_syntax(t_lex_lst *tokens);
char	**create_arr_cmd(char *word, char **arr_cmd);
int		add_first_rdir(t_lex_lst *tokens, t_cmd *cmd);
int		add_rest_rdirs(t_lex_lst *tokens, t_cmd *cmd);
t_cmd	*tkn_to_cmd(t_lex_lst *tokens);
void	free_cmds(t_cmd *cmds);
int		find_arr_size(char **array);

#endif
