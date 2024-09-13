/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/09/13 16:11:39 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "lexer.h"
#include "struct.h"
#include "parsing.h"
#include "execution.h"

void	init_struct(t_info *info, char **env)
{
//	char	**arr;

	info->rl = NULL;
	info->ex_stat = 0;
	info->envp = NULL;
	info->tokens = NULL;
	env_to_list(info, env);
//	print_env(info->envp);
//	arr = envlst_to_arr(info->envp);
//	print_char_arr(arr);
//	free_array(arr);
}
/*
int	do_shell(char *line, t_info *info)
{
	token = do_token(line, info);
	cmd = do_cmd(token, info);
	exito = executa(cmd, info);
	return (exito);
}*/

int	start_reading(t_info *info)
{
	t_cmd	*cmds;
	int		i;

	i = 0;
	while (1)
	{
		info->ex_stat = 0;
		info->rl = readline("our minishell: ");
		if (!info->rl)
			return (1);
		if (info->rl[0])
			add_history(info->rl);
		/*printf("user input: %s\n", info->rl);*/
		if(!valid_line(info))
		{
			free(info->rl);
			i++;
			continue;
		}
//		info->exit = do_shell(info->rl, info);
		if (!lexer(info))
			exit (0);
		print_lex_lst(info->tokens);
		if (simple_syntax(info->tokens) == 1)
		{
			free(info->rl);
			free_lexlst(info->tokens);
			info->ex_stat = 2;
			i++;
			printf("exit status: %d\n", info->ex_stat);
			continue;
		}
		cmds = tkn_to_cmd(info->tokens);
		print_cmds(cmds);
		free_lexlst(info->tokens);
		info->ex_stat = executor(cmds, info);
		printf("exit status: %d\n", info->ex_stat);
		free_cmds(cmds);
		info->tokens = NULL;
		free(info->rl);
		i++;
	}
	//rl_clear_history();
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	t_info	info;

	if (argc != 1)
	{
		printf("This program does not accept arguments\n");
		exit(1);
	}
	init_struct(&info, env);
	if (start_reading(&info))
	{
		free_envlst(info.envp);
		free_lexlst(info.tokens);
	}	
	return (info.ex_stat);
}
