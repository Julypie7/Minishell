/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:00:48 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/22 21:39:30 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef struct s_envp
{
	char 	*key;
	char	*value;
	struct s_envp 	*next;
} t_envp;

typedef	struct s_info
{
	char	*rl;
	int	ex_stat;
	t_envp	*envp;
} t_info;

// initial functions
void	start_reading(t_info *info);
void	init_struct(t_info *info, char **env);
int		main(int argc, char **argv, char **env);

//creating env copy
void	print_env(t_envp *lst);
void	print_char_arr(char **arr);
char	**free_array(char **array);
void	free_envlst(t_envp *envp);

void	add_node_to_env(t_envp **lst, t_envp *node);
int		find_equal(char *str);
void	env_to_list(t_info *info, char **env);
char	**envlst_to_arr(t_envp *envp);

#endif
