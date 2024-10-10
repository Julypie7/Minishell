/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/10/09 16:08:21 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "lexer.h"
#include "struct.h"
#include "parsing.h"
#include "execution.h"

int	init_struct(t_info *info, char **env)
{
	info->rl = NULL;
	info->ex_stat = 0;
	info->envp = env_to_list(env);
	if (!info->envp)
		return (1);
	info->copy = NULL;
	info->tokens = NULL;
	return (0);
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
		if (!cmds)
		{
			free_lexlst(info->tokens);
			free(info->rl);
			exit(-1); // malloc err
		}
	//	print_cmds(cmds);
		free_lexlst(info->tokens);
		info->ex_stat = executor(cmds, info);
		printf("exit status: %d\n", info->ex_stat);
		free_cmds(cmds);
		info->tokens = NULL;
//		rl_clear_history(info->rl);
		free(info->rl);
		i++;
	}
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
	if (init_struct(&info, env) == 1)
		return (-1);
	if (start_reading(&info))
	{
		free_envlst(info.envp);
		free_lexlst(info.tokens);
	}	
	return (info.ex_stat);
}
