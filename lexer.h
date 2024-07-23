/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:36:08 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/23 13:00:51 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
#include "minishell.h"

typedef	enum s_token
{
	PIPE;
	OUTPUT;
	APPEND;
	INPUT;
	HEREDOC;
} t_token


typedef struct s_lex_lst
{
	char	*str;
	t_token	token;
	int		elem;
	struct s_lex_lst	*next;
}	t_lexer_lst;

