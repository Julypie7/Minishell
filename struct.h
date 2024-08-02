/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:07:01 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/02 13:01:53 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

typedef struct s_envp
{
	char 	*key;
	char	*value;
	struct s_envp 	*next;
} t_envp;

typedef	enum s_type
{
	PIPE = 1,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
} t_type;


typedef struct s_lex_lst
{
	char	*word;
	t_type	type;
	char	*t_content;
	int	elem;
	struct s_lex_lst	*next;
}	t_lex_lst;

typedef	struct s_info
{
	char	*rl;
	t_lex_lst	*tokens;
	int	ex_stat;
	t_envp	*envp;
} t_info;

#endif
