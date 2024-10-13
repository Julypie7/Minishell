/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:10 by martalop          #+#    #+#             */
/*   Updated: 2024/10/13 04:37:46 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

// PIPEX UTILS
char	**prep_cmd_paths(char **env);
char	**join_for_path(char **paths);
char	**create_empty_array(void);
char	*find_path(char **paths, char **arr_cmd);
char	*check_cmd_access(char **paths, char *cmd);
// new
void	cmd_not_found(char *str);
int		find_slash(char *str);

// EXECUTION
int		heredoc(char *lim);
int		find_heredocs(t_cmd *cmds);
int		open_redir(t_cmd *cmd);
int		open_input(t_redir *tmp, t_cmd *cmd);
int		open_output(t_redir *tmp, t_cmd *cmd);
int		redirect(t_cmd *cmd);
int		count_cmds(char *rl);
int		executor(t_cmd *segmts, t_info *info);
int		exec_builtin(char **arr_cmd, t_info *info, \
		t_cmd *cmds, t_exec *exec_info);
int		exec_simp_cmd(t_cmd *cmd, t_info *info, t_exec *exec_info);
int		exec_mult_cmd(t_cmd *tmp, t_exec *exec_info, t_info *info);
void	simp_child_cmd(t_cmd *cmd, t_info *info, t_exec *exec_info);
void	mult_child(t_cmd *cmd, t_info *info, t_exec *exec_info);
void	print_cmds(t_cmd *cmds);
void	print_redirs_lst(t_redir *redirs);
void	free_redir_lst(t_redir *redirs);
void	free_cmds(t_cmd *cmds);
void	free_exec_info(t_exec *exec_info);
void	free_child(t_info *info, t_cmd *cmds, t_exec *exec_info);

// BUILTIN CHECK
int		fill_arr_b(char **arr_b);
int		find_cmd_type(char *str);

#endif
