/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:58:48 by martalop          #+#    #+#             */
/*   Updated: 2024/10/14 00:37:53 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "struct.h"

int		expand_files(t_redir *redirs, t_envp *envp, int prev_ex_stat);
int		expand_cmds(t_cmd *cmd, t_envp *envp, int prev_ex_stat);
char	*join_back_expanded(char **divided_arr);
char	**break_down_str(char *s);
int		find_quote_type(char *str);
char	**divide_str(char *str);
char	**join_all(char **arr);
char	**my_special_split(char *final_str);
char	**cmd_expansion(char **arr_cmd, t_envp *envp, int prev_ex_stat);
char	**divide_str(char *str);
char	**full_expansion(char *str, t_envp *envp, int prev_ex_stat);
char	**fill_words(char *s, char **array);
int		handle_new_word(char *s, int *i, char **array, int word);
int		handle_all(char *s, int *i, char **array);
int		split_simp_quote(char *s, int *i, char **array);
int		split_doubl_quote(char *s, int *i, char **array);
char	**another_special_split(char *s);
int		another_count_sections(char *s);
int		find_simp_quote(char *str);
int		find_double_quote(char *str);
void	skip_quote_content(const char *s, int *i);

#endif
