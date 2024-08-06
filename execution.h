/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:10 by martalop          #+#    #+#             */
/*   Updated: 2024/08/06 20:18:21 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

typedef struct s_cmd
{
	char	**arr_cmd;
 	char	*path;
 	char	**env;
 	int		redir[4];
	int		pid;
//	expansion ?
	struct s_cmd	*next;
}	t_cmd_info;

typedef	enum s_type
{
	OUTPUT = 1,
	APPEND,
	INPUT,
	HEREDOC,
} t_type;

typedef struct s_redir
{
	t_type	token;
	char	*file_name;
	int		fd;
	struct s_redir		*next;
} 	t_redir;

typedef struct s_lex_lst
{
	char	*word;
	t_type	type;
	char	*t_content; // string del token (por ej: "<<")
	int		file;
//	int	elem;
	struct s_lex_lst	*next;
}	t_lex_lst;

#endif
