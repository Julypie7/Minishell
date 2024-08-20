/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:10 by martalop          #+#    #+#             */
/*   Updated: 2024/08/20 14:39:28 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

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
//	int		fd_in; // para las redirs de input
//	int		fd_out; // para las redirs de output
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

typedef struct s_lex_lst
{
	char	*word;
	t_type	type;
	char	*t_content; // string del token (por ej: "<<")
	int		file;
//	int	elem;
	struct s_lex_lst	*next;
}	t_lex_lst;

// PIPEX UTILS
char	**prep_cmd_paths(char **env);
char	**join_for_path(char **paths);
char	**create_empty_array(void);
char	*find_path(char **paths, char **arr_cmd);
char	*check_cmd_access(char **paths, char *cmd);

// EXECUTION
int	heredoc(char *lim);

// BUILTIN CHECK
int	fill_arr_b(char **arr_b);
int	find_cmd_type(char *str);

#endif
