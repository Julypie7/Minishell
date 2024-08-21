/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineimatu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:56:35 by ineimatu          #+#    #+#             */
/*   Updated: 2024/08/21 15:14:20 by ineimatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	init_struct(t_info *info, char **env)
{
	char	**arr;

	info->rl = NULL;
	info->ex_stat = 0;
	info->envp = NULL;
	env_to_list(info, env);
//	print_env(info->envp);
	arr = envlst_to_arr(info->envp);
//	print_char_arr(arr);
	free_array(arr);
}

int	start_reading(t_info *info)
{
	int i;

	i = 0;
	while (i < 5)
	{
		info->rl = readline("our minishell > ");
		/*printf("user input: %s\n", info->rl);*/
		if(!valid_line(info))
		{
			free(info->rl);
			i++;
			continue;
		}
		if (!lexer(info))
			exit (0);
		//clasificar string
	//	print_lex_lst(info->tokens);
		free_lexlst(info->tokens);
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
