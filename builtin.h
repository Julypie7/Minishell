/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:01 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/10 12:14:06 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

//EXIT
int			mini_exit(char **av, t_info *info, t_cmd *cmds, t_exec *exec_info);
long long	ft_atoi_ex(char *str);
void		check_arg(char *arg, t_info *info, t_cmd *cmd, t_exec *exec_info);
void		exit_error(t_info *info, int ex_st, t_cmd *cmds, t_exec *exec_info);
void		ft_exit(t_info *info, int ex_stat, t_cmd *cmd, t_exec *exec_info);
int			check_long(char *arg, t_info *info, t_cmd *cmds, t_exec *exec_info);
int			check_zero_case(char *str, t_info *info, t_cmd *cmds, \
		t_exec *exec_info);

//ENV
int			mini_env(char **argv, t_info *info);

//PWD
int			mini_pwd(t_envp *lst);

//ECHO
int			mini_echo(char **argv);
int			size_of_argv(char **argv);
void		print_echo(char **argv, int i);

//UNSET
t_envp		*do_unset(t_envp *list, t_envp *to_unset);
int			mini_unset(char **argv, t_info *info);

//CD
int			mini_cd(char **argv, t_info *info);
int			just_cd(t_envp *lst, char *path, t_info *info);
void		change_pwd(t_envp *lst);
char		*ft_getenv(char *str, t_envp *lst);
void		free_pwd(char *pwd);

//EXPORT
int			mini_export(char **argv, t_info	*info);
int			copy_process(t_envp *first, t_envp *new_env, t_info *info);
int			copy_env(t_info *info, t_envp *env);
int			check_special_characters(char c);
int			parse_export(char *str);
int			check_of_arg(char **argv, int len, t_info *info);
int			how_much(char **argv, t_info *info);
int			change_copy_equal(char *export, t_envp *copy, int i);
int			equal(char *export, int i, t_envp *tmp, t_info *info);
int			check_keys(t_info *info, char *export);
t_envp		*sort_alg(t_envp *lst_export, t_envp *sorted);
void		print_env_sorted(t_info *info);
int			check_change_copy(t_envp *copy, char *export, int i);
int			add_node_to_copy(t_info *info, t_envp *env, char *export);
int			not_in_env(t_info *info, char *export);
int			plus_sign(char *str, int equal);
int			add_node_ch_val(t_envp *tmp, int i, char *export);
int			add_node_without_val(t_envp *tmp, int i, char *export);
int			copy_without_equal(t_envp *tmp, char *export, int i, int q);
int			copy_with_eq(t_envp *tmp, char *export, int i);
int			exists_in_env(t_envp *env, char *export);
int			exists_in_copy(t_envp *env, char *export);
int			handle_env_copy(t_info *info, char *export, int i, int flag);

//void	ft_putstr_fd(char *s, int fd);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strcpy(char *s1, char *s2);

#endif
