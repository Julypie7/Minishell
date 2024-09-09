/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:10 by martalop          #+#    #+#             */
/*   Updated: 2024/09/09 17:00:36 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

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
int		open_redir(t_redir *redirs);
int		redirect(t_redir *redirs);
int		count_cmds(char *rl);
int		exec_simp_cmd(t_cmd *cmd, t_info *info, t_exec *exec_info);
int		exec_mult_cmd(t_cmd *tmp, t_exec *exec_info, t_info *info);
void	print_cmds(t_cmd *cmds);
void	print_redirs_lst(t_redir *redirs);
void	free_redir_lst(t_redir *redirs);
void	free_cmds(t_cmd *cmds);
void	free_exec_info(t_exec *exec_info);

// BUILTIN CHECK
int		fill_arr_b(char **arr_b);
int		find_cmd_type(char *str);

#endif
