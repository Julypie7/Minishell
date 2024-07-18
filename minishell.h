/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:00:48 by ineimatu          #+#    #+#             */
/*   Updated: 2024/07/18 16:23:21 by martalop         ###   ########.fr       */
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
} t_envp

typedef	struct s_info
{
	char	*rl;
	int	ex_stat;
	t_envp	envp;
} t_info

int	main(int argc, char **argv, char **env);

#endif
