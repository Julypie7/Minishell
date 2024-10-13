/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 22:58:48 by martalop          #+#    #+#             */
/*   Updated: 2024/10/12 22:59:28 by martalop         ###   ########.fr       */
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
char	**cmd_expansion(char **arr_cmd, t_envp *envp, int prev_ex_stat, \
		int *malloc_flag);

#endif
