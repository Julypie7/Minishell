/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:36:08 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/30 14:59:32 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
#include "minishell.h"
#include "struct.h"


void	valid_line(t_info *info);
int lexer(t_info *info);
int	add_node(char *str, char *token, int q, t_info *info);
int	handle_quotes(t_info *info, int i);
int	check_token(t_info *info, int i);
int	token_exist(char token);
void	exit_free(char *str, int i, t_info *info);
void	free_lexlst(t_lex_lst *tokens);
int	handle_word(t_info *info, int i);

#endif
