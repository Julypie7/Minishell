/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:07:01 by ineimatu          #+#    #+#             */
/*   Updated: 2024/09/09 15:00:34 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "minishell.h"

typedef	enum s_type
{
	PIPE = 1,
	OUTPUT,
	APPEND,
	INPUT,
	HEREDOC,
} t_type;


typedef struct s_redir
{
	t_type	token;
	char	*file_name;
	int		fd; // luego la quitoo
	struct s_redir		*next;
} 	t_redir;

typedef struct s_cmd
{
	char	**arr_cmd;
 	char	*path;
 	char	**env;
	int		pid;
	int		fd_in; // para las redirs de input
	int		fd_out; // para las redirs de output
//(se van actualizando prq los voy sobreescribiendo)
	t_redir	*redirs;
	int		indx; // cuál comando es
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**paths;
	int		or_fd[2];
	int		cmd_num;
	int		pipe_end[2];
}	t_exec;


typedef struct s_envp
{
	char 	*key;
	char	*value;
	struct s_envp 	*next;
} t_envp;

typedef struct s_lex_lst
{
	char	*word;
	t_type	type;
	char	*t_content;
	//int	elem;
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
